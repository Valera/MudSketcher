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
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    scene->addItem(new Room(Room::Lava));
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
