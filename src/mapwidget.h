#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsScene>

#include "arrow.h"

class MapWidget : public QGraphicsScene
{
Q_OBJECT
public:
    explicit MapWidget(QObject *parent = 0);

    void drawBackground ( QPainter * painter, const QRectF & rect );
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );

    Arrow * addArrow ( qreal x1, qreal y1, qreal x2, qreal y2);
signals:   

public slots:

private:
    bool m_fFirstMove;

};

#endif // MAPWIDGET_H
