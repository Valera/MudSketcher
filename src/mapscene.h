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

#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>

#include "arrow.h"
#include "room.h"
#include "reader.h"

class MapScene : public QGraphicsScene
{
Q_OBJECT
public:
    MapScene(QObject *parent = 0, int horSize = 10, int vertSize = 10, QString name = QString());
    MapScene(QObject *parent, SExpr *zone);

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

    bool isValid();

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
