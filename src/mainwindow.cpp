#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRectF>
#include <QPointF>

#include "room.h"
#include "mapwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene * scene = new MapWidget;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(0,0, 10, 10);
            //QRectF(QPointF(-10, -10), ui->graphicsView->size()));
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    scene->addEllipse(QRectF(-100.0, -100.0, 100.0, 100.0));
    scene->addItem(new Room());
    //ui->graphicsView->s
    //ui->graphicsView->scale(3,3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
