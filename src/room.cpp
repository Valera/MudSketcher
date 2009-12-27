#include "room.h"
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>

#include "utils.h"

Room::Room()
{
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
    qreal a = 2;
    return QRectF(-10 -a, -10 -a , 20 + 2*a, 20 + 2*a);
}

void Room::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
    painter->setPen(Qt::lightGray);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(-8, -8, 20, 20);
    painter->setPen(Qt::darkGreen);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(-10, -10, 20, 20);


    /*
    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
    */
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
