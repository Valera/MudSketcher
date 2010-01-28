#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRectF>
#include <QPointF>

#include "room.h"
#include "mapscene.h"
#include "roomproperties.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MapScene * scene = new MapScene;
    ui->graphicsView->setScene(scene);
    RoomProperties *rp = new RoomProperties(this);
    ui->horizontalLayout->insertWidget(0, rp, 0 );
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    scene->addItem(new Room(Room::Lava));
    connect(rp, SIGNAL(roomTypeChanged(int)), scene, SLOT(setCurrentRoomType(int)));
    connect(rp, SIGNAL(roomFlagsChanged(Room::Flags)), scene, SLOT(setCurrentRoomFlags(Room::Flags)));
    connect(rp, SIGNAL(roomShortDescriptionChanged(QString)), scene, SLOT(setCurrentRoomShortDescription(QString)));
    connect(rp, SIGNAL(roomLongDescriptionChanged(QString)), scene, SLOT(setCurrentRoomLongDescription(QString)));
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
