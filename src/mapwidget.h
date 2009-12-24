#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsScene>

class MapWidget : public QGraphicsScene
{
Q_OBJECT
public:
    explicit MapWidget(QObject *parent = 0);

    void drawBackground ( QPainter * painter, const QRectF & rect );
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
signals:

public slots:

};

#endif // MAPWIDGET_H
