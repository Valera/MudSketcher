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

#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsItem>

#include <QPen>
#include <QLineF>

class Arrow : public QGraphicsItem
{
public:
    Arrow( QGraphicsItem * parent = 0 );
    Arrow( qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent = 0 );
    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    enum { Type = UserType + 2 };
    int type() const { return Type; }

    bool isActive() { return m_active; };

private:
    bool m_active;
    QPen m_hoverPen;
    QPen m_stdPen;
    QPen m_pen;
    QLineF m_line;
};

#endif // ARROW_H
