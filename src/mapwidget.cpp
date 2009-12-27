#include "mapwidget.h"

#include <QPainter>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "room.h"
#include "utils.h"

MapWidget::MapWidget(QObject *parent) :
    QGraphicsScene(parent)
{
}

const int CELLSIZE = 20;
const int NCELLS = 10;

void MapWidget::drawBackground ( QPainter * painter, const QRectF & rect )
{
    Q_UNUSED(rect);
    QPen pen(Qt::lightGray);
    pen.setCosmetic(true);
    pen.setWidth(0);
    painter->setPen(pen);
    for(int x = 0; x < NCELLS + 1; x++){
        painter->drawLine(x*CELLSIZE, 0, x*CELLSIZE, NCELLS*CELLSIZE);
    }
    for(int y = 0; y < NCELLS + 1; y++){

        painter->drawLine(0, y*CELLSIZE, NCELLS*CELLSIZE, y*CELLSIZE);
    }
}

void MapWidget::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )\
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    if(mouseGrabberItem()){
        m_fFirstMove = true;
    }
}

void MapWidget::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
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

void MapWidget::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    const int step = 40;
    //int x = step * (int(mouseEvent->scenePos().x()) / step);
    int x = roundBy(mouseEvent->scenePos().x(), step);
    //int y = step * (int(mouseEvent->scenePos().y()) / step);
    int y = roundBy(mouseEvent->scenePos().y(), step);
    qDebug() << mouseEvent->scenePos().x() << mouseEvent->scenePos().y();
    qDebug() << x << y;
    if(itemAt(QPointF(x, y - step)))
        addArrow(x, y, x, y - step);
    if(itemAt(QPointF(x, y + step)))
        addArrow(x, y, x, y + step);
    if(itemAt(QPointF(x - step, y)))
        addArrow(x, y, x - step, y);
    if(itemAt(QPointF(x + step, y)))
        addArrow(x, y, x + step, y);
    Room *r = new Room();
    addItem(r);
    r->setPos(x, y);
}

Arrow * MapWidget::addArrow ( qreal x1, qreal y1, qreal x2, qreal y2)
{
    Arrow *a = new Arrow(x1, y1, x2, y2);
    addItem(a);
    //addLine(x1, y1, x2, y2);
    return a;
}
