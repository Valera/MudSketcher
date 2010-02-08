#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>

#include "arrow.h"
#include "room.h"

class MapScene : public QGraphicsScene
{
Q_OBJECT
public:
    explicit MapScene(QObject *parent = 0, int horSize = 10, int vertSize = 10, QString name = QString());

    void drawBackground ( QPainter * painter, const QRectF & rect );
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void emitPropertiesChangeSignals ();

    void linkRoom(QGraphicsItem *room);
    Arrow * addArrow ( qreal x1, qreal y1, qreal x2, qreal y2);
    Room* currentRoom();
    QString zoneText();

    QString zoneName()  { return m_zoneName; };
    void setZoneName(QString name) { m_zoneName = name; };

    int zoneHeight() { return m_zoneHeight; };
    void setZoneHeight(int h) { m_zoneHeight = h; };

    int zoneWidth() { return m_zoneWidth; };
    void setZoneWidth(int w) { m_zoneWidth = w; };

signals:
    void currentRoomChanged(Room *current);

public slots:
    void setCurrentRoomType(int type);
    void setCurrentRoomFlags(Room::Flags flags);
    void setCurrentRoomShortDescription(QString);
    void setCurrentRoomLongDescription(QString);
    void emitRoomChange();

private:
    bool m_fFirstMove;
    Room::RoomType m_roomType;
    QString m_zoneName;
    int m_zoneHeight;
    int m_zoneWidth;
};

#endif // MAPSCENE_H
