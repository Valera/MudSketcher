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

private:
    bool m_active;
    QPen m_hoverPen;
    QPen m_stdPen;
    QPen m_pen;
    QLineF m_line;
};

#endif // ARROW_H
