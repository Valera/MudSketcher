#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>

#include "arrow.h"
#include "room.h"

class MapScene : public QGraphicsScene
{
Q_OBJECT
public:
    explicit MapScene(QObject *parent = 0);

    void drawBackground ( QPainter * painter, const QRectF & rect );
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void emitPropertiesChangeSignals ();

    void linkRoom(QGraphicsItem *room);
    Arrow * addArrow ( qreal x1, qreal y1, qreal x2, qreal y2);
    Room* currentRoom();
signals:

public slots:
    void setCurrentRoomType(int type);
    void setCurrentRoomFlags(Room::Flags flags);
    void setCurrentRoomShortDescription(QString);
    void setCurrentRoomLongDescription(QString);

private:
    bool m_fFirstMove;
    Room::RoomType m_roomType;
};

#endif // MAPSCENE_H
