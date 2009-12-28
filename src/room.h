#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsItem>

class Room : public QGraphicsItem
{
public:
    enum RoomType { Usual, Lava, Hills, Unknown };

    Room(RoomType rt);
    ~Room();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    RoomType roomType;

};

#endif // ROOM_H
