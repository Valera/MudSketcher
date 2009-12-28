#include "room.h"
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>

#include "utils.h"

Room::Room(RoomType rt) : QGraphicsItem ()
{
    roomType = rt;
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
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
    return QRectF(-10 - adjust, -10 -adjust, 20 + 2 * adjust, 20 + 2 * adjust);
}

void Room::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);

    // Shadow.
    painter->setPen(Qt::lightGray);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(-8, -8, 20, 20);

    // Room itself.
    switch(roomType){
    case Usual:
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
