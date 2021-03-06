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

#include "room.h"
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>

#include "utils.h"
#include <QDebug>

Room::Room(RoomType rt) : QGraphicsItem ()
{
    m_roomType = rt;
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(10);
}

Room::~Room()
{
}

QRectF Room::boundingRect() const
{
    /*const qreal adjust = 100;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
                  */
    qreal adjust = 2;
    return QRectF(-10 - adjust, -10 -adjust, 21 + 2 * adjust, 21 + 2 * adjust);
}

void Room::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);

    if (isSelected()){ // If selected, draw blue background.
        painter->setPen(Qt::lightGray);
        painter->setBrush(Qt::darkBlue);
        painter->drawEllipse(-16, -16, 32, 32);
    } else { // Elase draw simple shadow.
        painter->setPen(Qt::lightGray);
        painter->setBrush(Qt::lightGray);
        painter->drawRect(-8, -8, 20, 20);
    }
    // Room itself.
    switch(m_roomType){
    case City:
        painter->setPen(Qt::darkGreen);
        painter->setBrush(Qt::darkGray);
        painter->drawRect(-10, -10, 20, 20);
        break;
    case Lava:
        painter->setPen(Qt::red);
        painter->setBrush(Qt::darkGray);
        painter->drawRect(-10, -10, 20, 20);
        break;
    case Hills:
        painter->setPen(Qt::darkGray);
        painter->setBrush(Qt::darkGreen);
        painter->drawRect(-10, -10, 20, 20);
        break;
    case Indoors:
        painter->setPen(QColor(0x80, 0x3F, 0x08));
        painter->setBrush(qColorFromHex("#F0D25F"));
        painter->drawRect(-10, -10, 20, 20);
        break;
    case Field:
        painter->setPen(QColor(0x80, 0x3F, 0x08));
        painter->setBrush(QColor(0xA9, 0xDD, 0x3E));
        painter->drawRect(-10, -10, 20, 20);
        break;
    case Forest:
        painter->setPen(QColor(0x80, 0x3F, 0x08));
        painter->setBrush(QColor(0x49, 0x8A, 0x17));
        painter->drawRect(-10, -10, 20, 20);
        break;
    case Mountains:
        painter->setPen(Qt::lightGray);
        painter->setBrush(Qt::darkGray);
        painter->drawRect(-10, -10, 20, 20);
        painter->setPen(Qt::white);
        painter->drawText(-10, -10, 20, 20,  Qt::AlignCenter, "^");
        break;
    case Unknown:
    default: // Unknown room type;
        painter->setPen(Qt::gray);
        painter->setBrush(Qt::lightGray);
        painter->drawRect(-10, -10, 20, 20);
        painter->setPen(Qt::white);
        painter->drawText(-10, -10, 20, 20,  Qt::AlignCenter, "?");
        break;
    }
}

QVariant Room::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        newPos.setX(roundBy(newPos.x(), 40));
        newPos.setY(roundBy(newPos.y(), 40));
        //newPos.setX(0);
        /*
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
        */
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void Room::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Room::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QString Room::roomTypeName(RoomType type)
{
    // Hills, City, Indoors, Field, Forest, Mountains, Lava, Unknown
    switch(type){
    case Hills:
        return QString::fromUtf8("Холмы");
        break;
    case City:
        return QString::fromUtf8("Город");
        break;
    case Indoors:
        return QString::fromUtf8("Помещение");
        break;
    case Field:
        return QString::fromUtf8("Поле");
        break;
    case Forest:
        return QString::fromUtf8("Лес");
        break;
    case Mountains:
        return QString::fromUtf8("Горы");
        break;
    case Lava:
        return QString::fromUtf8("Лава");
        break;
    default:
        return QString("Неизвестный тип");
        break;
    }
}

QString Room::sExpr()
{
    int _x = roundBy(x(), 40) / 40;
    int _y = roundBy(y(), 40) / 40;

    QString roomDesc;
    if(roomShortDescription().isEmpty())
        roomDesc = QString("nil");
    else
        roomDesc = roomShortDescription();

    QString type;
    switch (roomType()){ // Hills, City, Indoors, Field, Forest, Mountains, Lava, Unknown
    case Hills:
        type = ":hills";
        break;
    case City:
        type = ":city";
        break;
    case Indoors:
        type = ":indoors";
        break;
    case Field:
        type = ":field";
        break;
    case Forest:
        type = ":forest";
        break;
    case Mountains:
        type = ":mountains";
        break;
    case Lava:
        type = ":lava";
        break;
    case Unknown: // Fallthrough.
    default:
        type = ":unknown";
        break;
    }

    QString flagList("( ");
    if (m_flags & Peacefull) flagList += ":peace ";
    if (m_flags & NoMob) flagList += ":nomob ";
    if (m_flags & Dark) flagList += ":dark ";
    if (m_flags & Tunnel) flagList += ":tunnel ";
    if (m_flags & Service) flagList += ":service ";
    flagList += ")";

    return QString("(:coord (%1 %2) :room-short-description %3 :room-long-description %4 :room-type %5 :room-flags %6)")
            .arg(_x).arg(_y).arg(toLispString(roomShortDescription())).arg(toLispString(roomLongDescription()))
            .arg(type).arg(flagList);
}
