#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsItem>

class Room : public QGraphicsItem
{
public:
    // This enum should be iteratable , e.g. without assignments, and end with Unknown.
    enum RoomType { Hills, City, Indoors, Field, Forest, Mountains, Lava, Unknown };
    void setRoomType (RoomType roomType) { m_roomType = roomType; update(); };

    Room(RoomType rt);
    ~Room();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    static QString roomTypeName(RoomType type);

private:
    RoomType m_roomType;
};

#endif // ROOM_H
