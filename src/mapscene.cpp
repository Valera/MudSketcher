/*
    MudSketcher, program for building LispMud zones.
    Copyright (C) 2009  Valeriy Fedotov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mapscene.h"

#include <QPainter>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "room.h"
#include "utils.h"

const int CELLSIZE = 20;
const int NCELLS = 10;
const int ROOMSTEP = 2 * CELLSIZE;

MapScene::MapScene(QObject *parent, int horSize, int vertSize, QString name) :
    QGraphicsScene(parent)
{
    m_zoneHeight = vertSize;
    m_zoneWidth = horSize;
    m_zoneName = name;

    const int adjust = 40;
    setSceneRect(-adjust, -adjust,
                 m_zoneWidth*2*CELLSIZE + 2 * adjust, m_zoneHeight*2*CELLSIZE + 2 * adjust);
    connect(this, SIGNAL(selectionChanged()), this, SLOT(emitRoomChange()));
}


void MapScene::drawBackground ( QPainter * painter, const QRectF & rect )
{
    Q_UNUSED(rect);
    QPen pen(Qt::lightGray);
    pen.setCosmetic(true);
    pen.setWidth(0);
    painter->setPen(pen);
    for(int x = 0; x <= 2 * m_zoneWidth; x++){
        painter->drawLine(x*CELLSIZE, 0, x*CELLSIZE, 2*m_zoneHeight*CELLSIZE);
    }
    for(int y = 0; y <= 2 * m_zoneHeight; y++){
        painter->drawLine(0, y*CELLSIZE, 2*m_zoneWidth*CELLSIZE, y*CELLSIZE);
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
    int x = roundBy(mouseEvent->scenePos().x(), ROOMSTEP);
    int y = roundBy(mouseEvent->scenePos().y(), ROOMSTEP);
    if (itemAt(x, y))
        return;// Do not make new room in place where one exists.
    qDebug() << "Creating room with type " << m_roomType;
    Room *r = new Room(Room::RoomType(m_roomType));
    addItem(r);
    r->setPos(x, y);
    linkRoom(r);
    r->setSelected(true);
}

// Links room with neighbours with arrows.
void MapScene::linkRoom(QGraphicsItem *room)
{
    int x = room->pos().x();
    int y = room->pos().y();
    QGraphicsItem *arrow = itemAt(room->pos() + QPointF(-20, 0));
    if(!arrow && itemAt(room->pos() + QPointF(-ROOMSTEP, 0)))
            addArrow(x -5, y, x - ROOMSTEP + 5, y);
    arrow = itemAt(room->pos() + QPointF(+20, 0));
    if(!arrow && itemAt(room->pos() + QPointF(ROOMSTEP, 0)))
            addArrow(x +5, y, x + ROOMSTEP - 5, y);
    arrow = itemAt(room->pos() + QPointF(0, 20));
    if(!arrow && itemAt(room->pos() + QPointF(0, ROOMSTEP)))
            addArrow(x, y + 5, x, y + ROOMSTEP - 5);
    arrow = itemAt(room->pos() + QPointF(0, -20));
    if(!arrow && itemAt(room->pos() + QPointF(0, -ROOMSTEP)))
            addArrow(x, y - 5, x, y - ROOMSTEP + 5);
}

Arrow* MapScene::addArrow ( qreal x1, qreal y1, qreal x2, qreal y2)
{
    Arrow *a = new Arrow(x1, y1, x2, y2);
    addItem(a);
    return a;
}

Room* MapScene::currentRoom()
{
    QList<QGraphicsItem *> selected = selectedItems ();
    if ( selected.length() == 1 &&  selected[0]->type() == Room::Type ){
        return qgraphicsitem_cast <Room *> (selected[0]);
    }else{
        return 0;
    }
}

void MapScene::setCurrentRoomType(int type)
{
    m_roomType = Room::RoomType(type);
    Room *r = currentRoom();
    if(r)
        r->setRoomType(m_roomType);
};

void MapScene::setCurrentRoomFlags(Room::Flags flags)
{
    Room *r = currentRoom();
    if(r)
        r->setRoomFlags(flags);
}

void MapScene::setCurrentRoomShortDescription(QString str)
{
    Room *r = currentRoom();
    if(r)
        r->setRoomShortDescription(str);
}

void MapScene::setCurrentRoomLongDescription(QString str)
{
    qDebug() << "set long descr" << str;
    Room *r = currentRoom();
    if(r)
        r->setRoomLongDescription(str);
}

void MapScene::emitRoomChange()
{
    Room *r = currentRoom();
    emit currentRoomChanged(r);
}

QString MapScene::zoneText()
{
    QString result;

    result += QString( "(:zone-name %1\n :zone-size (%2 %3) :zone-rooms\n(\n")
              .arg(toLispString(m_zoneName)).arg(m_zoneHeight).arg(m_zoneWidth);

    QList<QGraphicsItem *> list;
    list = items();
    QGraphicsItem *i;
    foreach(i, list){
        Room *r;
        if ( (r = qgraphicsitem_cast<Room *>(i)) ){
            result += "\n";
            result += r->sExpr();

            result.remove(result.length()-1, 1);
            Arrow *arrow;
            Room  *room;
            arrow = qgraphicsitem_cast <Arrow *> (itemAt(r->pos() + QPointF(-CELLSIZE, 0)));
            room  = qgraphicsitem_cast <Room  *> (itemAt(r->pos() + QPointF(-ROOMSTEP, 0)));
            if(room && arrow && arrow->isActive())
            {
                result += QString("\n\t\t:west-exit (:exit-description %1 :door nil) ")
                          .arg(toLispString(room->roomShortDescription()));
            }
            arrow = qgraphicsitem_cast <Arrow *> (itemAt(r->pos() + QPointF(CELLSIZE, 0)));
            room  = qgraphicsitem_cast <Room  *> (itemAt(r->pos() + QPointF(ROOMSTEP, 0)));
            if(room && arrow && arrow->isActive())
            {
                result += QString("\n\t\t:east-exit (:exit-description %1 :door nil) ")
                          .arg(toLispString(room->roomShortDescription()));
            }
            arrow = qgraphicsitem_cast <Arrow *> (itemAt(r->pos() + QPointF(0, -CELLSIZE)));
            room  = qgraphicsitem_cast <Room  *> (itemAt(r->pos() + QPointF(0, -ROOMSTEP)));
            if(room && arrow && arrow->isActive())
            {
                result += QString("\n\t\t:north-exit (:exit-description %1 :door nil) ")
                          .arg(toLispString(room->roomShortDescription()));
            }
            arrow = qgraphicsitem_cast <Arrow *> (itemAt(r->pos() + QPointF(0, CELLSIZE)));
            room  = qgraphicsitem_cast <Room  *> (itemAt(r->pos() + QPointF(0, ROOMSTEP)));
            if(room && arrow && arrow->isActive())
            {
                result += QString("\n\t\t:south-exit (:exit-description %1 :door nil) ")
                          .arg(toLispString(room->roomShortDescription()));
            }
            result += "\n)";
        }
    }
    result += "\n)\n"; // Room list.

    result += ")\n";

    return result;
}

bool MapScene::isValid()
// Returns true if zone can be saved to file.
{
    QList<QGraphicsItem *> list = items();
    QGraphicsItem *i;
    bool valid = true;
    foreach(i, list){
        Room *r;
        if ( (r = qgraphicsitem_cast<Room *>(i)) ){
            int _x = roundBy(r->x(), ROOMSTEP) / ROOMSTEP;
            int _y = roundBy(r->y(), ROOMSTEP) / ROOMSTEP;
            if ( _x < 0 || _x > m_zoneWidth || _y < 0 || _y > m_zoneHeight ){
                valid  = false;
                break;
            }
        }
    }
    return valid;
}
