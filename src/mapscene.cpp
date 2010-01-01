#include "mapscene.h"

#include <QPainter>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "room.h"
#include "utils.h"

const int CELLSIZE = 20;
const int NCELLS = 10;

MapScene::MapScene(QObject *parent) :
    QGraphicsScene(parent)
{
    const int adjust = 40;
    setSceneRect(-adjust, -adjust,
                 NCELLS*CELLSIZE + 2 * adjust, NCELLS*CELLSIZE + 2 * adjust);
}


void MapScene::drawBackground ( QPainter * painter, const QRectF & rect )
{
    Q_UNUSED(rect);
    QPen pen(Qt::lightGray);
    pen.setCosmetic(true);
    pen.setWidth(0);
    painter->setPen(pen);
    for(int x = 0; x <= NCELLS; x++){
        painter->drawLine(x*CELLSIZE, 0, x*CELLSIZE, NCELLS*CELLSIZE);
    }
    for(int y = 0; y <= NCELLS; y++){

        painter->drawLine(0, y*CELLSIZE, NCELLS*CELLSIZE, y*CELLSIZE);
    }
}

void MapScene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )\
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    if(mouseGrabberItem()){
        m_fFirstMove = true;
    }
}

void MapScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if(mouseGrabberItem() && m_fFirstMove){
        QList<QGraphicsItem *> exits = collidingItems(mouseGrabberItem());
        foreach(QGraphicsItem *i, exits){
            if(i->type() == Arrow::Type){
                removeItem(i);
                delete i;
            }
        }
        m_fFirstMove = false;
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void MapScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QGraphicsItem *room = mouseGrabberItem();
    if(room){
        qDebug() << items(room->pos());
        linkRoom(room);
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void MapScene::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    const int step = 40;
    int x = roundBy(mouseEvent->scenePos().x(), step);
    int y = roundBy(mouseEvent->scenePos().y(), step);
    qDebug() << "Creating room with type " << m_roomType;
    Room *r = new Room(Room::RoomType(m_roomType));
    addItem(r);
    r->setPos(x, y);
    linkRoom(r);
}

// Links room with neighbours with arrows.
void MapScene::linkRoom(QGraphicsItem *room)
{
    int x = room->pos().x();
    int y = room->pos().y();
    QGraphicsItem *arrow = itemAt(room->pos() + QPointF(-20, 0));
    if(!arrow && itemAt(room->pos() + QPointF(-40, 0)))
            addArrow(x -5, y, x - 35, y);
    arrow = itemAt(room->pos() + QPointF(+20, 0));
    if(!arrow && itemAt(room->pos() + QPointF(40, 0)))
            addArrow(x +5, y, x + 35, y);
    arrow = itemAt(room->pos() + QPointF(0, 20));
    if(!arrow && itemAt(room->pos() + QPointF(0, 40)))
            addArrow(x, y + 5, x, y + 35);
    arrow = itemAt(room->pos() + QPointF(0, -20));
    if(!arrow && itemAt(room->pos() + QPointF(0, -40)))
            addArrow(x, y - 5, x, y - 35);
}

Arrow* MapScene::addArrow ( qreal x1, qreal y1, qreal x2, qreal y2)
{
    Arrow *a = new Arrow(x1, y1, x2, y2);
    addItem(a);
    return a;
}

void MapScene::setRoomType(int type)
{
    m_roomType = Room::RoomType(type);
    QList<QGraphicsItem *> selected = selectedItems ();
    if ( selected.length() == 1 &&  selected[0]->type() == Room::Type )
    {
        (qgraphicsitem_cast <Room *> (selected[0]))->setRoomType(m_roomType);
    }
};

