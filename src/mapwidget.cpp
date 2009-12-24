#include "mapwidget.h"

#include <QPainter>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "room.h"

MapWidget::MapWidget(QObject *parent) :
    QGraphicsScene(parent)
{
}

const int CELLSIZE = 20;
const int NCELLS = 10;

void MapWidget::drawBackground ( QPainter * painter, const QRectF & rect )
{
    QPen pen(Qt::lightGray);
    pen.setCosmetic(true);
    pen.setWidth(0);
    painter->setPen(pen);
    for(int x = 0; x < NCELLS + 1; x++){
        painter->drawLine(x*CELLSIZE, 0, x*CELLSIZE, NCELLS*CELLSIZE);
    }
    for(int y = 0; y < NCELLS + 1; y++){

        painter->drawLine(0, y*CELLSIZE, NCELLS*CELLSIZE, y*CELLSIZE);
    }
}

int roundBy(qreal value, int roundStep)
{
    return roundStep * (int(value + roundStep / 2.0) / roundStep);
}

void MapWidget::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    const int step = 20;
    //int x = step * (int(mouseEvent->scenePos().x()) / step);
    int x = roundBy(mouseEvent->scenePos().x(), step);
    //int y = step * (int(mouseEvent->scenePos().y()) / step);
    int y = roundBy(mouseEvent->scenePos().y(), step);
    qDebug() << mouseEvent->scenePos().x() << mouseEvent->scenePos().y();
    qDebug() << x << y;
    Room *r = new Room();
    addItem(r);
    r->setPos(x, y);
}

