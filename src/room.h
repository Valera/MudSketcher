#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsItem>
#include <QObject>

class Room : public QGraphicsItem
{
public:
    // ---- Section with room data for output to zone files. ----
    // This enum should be iteratable , e.g. without assignments, and end with Unknown.
    enum RoomType {
        Hills, City, Indoors, Field, Forest, Mountains, Lava, Unknown
    };
    void setRoomType (RoomType roomType) { m_roomType = roomType; update(); };
    RoomType roomType() { return m_roomType; };

    enum Flag {
        Peacefull = 0x1,
        NoMob = 0x2,
        Dark = 0x4,
        Tunnel = 0x8,
        Service =  0x10,
    };
    Q_DECLARE_FLAGS(Flags, Flag);

    void setRoomFlags (Flags flags) { m_flags = flags; };
    Flags roomFlags () { return m_flags; };

    void setRoomShortDescription (QString shortDescription) { m_shortDescription = shortDescription; };
    QString roomShortDescription () {return m_shortDescription; };

    void setRoomLongDescription (QString longDescription) { m_longDescription = longDescription; };
    QString roomLongDescription () {return m_longDescription; };

    // ---- Section for proper inheriting of QGraphicsItem and overloading its methods. ----
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
    // ---- Section with room data for output to zone files. ----
    RoomType m_roomType;

    Flags m_flags;

    QString m_shortDescription;
    QString m_longDescription;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(Room::Flags)

#endif // ROOM_H
