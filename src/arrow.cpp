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

#include "arrow.h"

#include <QPen>
#include <QPainter>
#include <QDebug>
#include <math.h>

/*
Arrow::Arrow( QGraphicsItem * parent ) : QGraphicsItem(parent)
{
    setAcceptHoverEvents(true);
    m_active = true;
    m_hoverPen = QPen(QColor (0xF7, 0xB3, 0x4C));
    m_hoverPen.setWidth(2);
    m_stdPen = QPen (Qt::darkGray);
    m_stdPen.setWidth(2);
    m_pen = m_stdPen;
}
*/

Arrow::Arrow( qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent )
    : QGraphicsItem(parent)
{
    setAcceptHoverEvents(true);
    m_active = true;
    m_hoverPen = QPen(QColor (0xF7, 0xB3, 0x4C));
    m_hoverPen.setWidth(2);
    m_stdPen = QPen (Qt::darkGray);
    m_stdPen.setWidth(2);
    m_pen = m_stdPen;
    m_line = QLineF(x1, y1, x2, y2);
}

void Arrow::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    Q_UNUSED(event);
    m_pen = m_hoverPen;
    update();
}

void Arrow::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    Q_UNUSED(event);
    m_pen = m_stdPen;
    update();
}


QRectF Arrow::boundingRect() const
{
    const qreal a = 4;
    qreal x = fmin(m_line.x1(), m_line.x2());
    qreal w = fabs(m_line.x1() - m_line.x2());
    qreal y = fmin(m_line.y1(), m_line.y2());
    qreal h = fabs(m_line.y1() - m_line.y2());
    return QRectF(x - a, y - a, w + 2 * a, h + 2 * a);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option);
    painter->setPen(m_pen);
    painter->drawLine(m_line);
}

void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event;
    m_active = ! m_active;
    if ( m_active ){
        m_stdPen = QPen (Qt::darkGray);
        qDebug() << "t";
    }else{
        m_stdPen = QPen (QColor(0xBF, 0xD9, 0xE6)); // #BFD9E6
        qDebug() << "f";
    }
    m_stdPen.setWidth(2);
    update();
    QGraphicsItem::mousePressEvent(event);
}
