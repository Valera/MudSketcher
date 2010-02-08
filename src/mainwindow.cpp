#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRectF>
#include <QPointF>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

#include "room.h"
#include "mapscene.h"
#include "roomproperties.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    m_mapScene = new MapScene;
    ui->graphicsView->setScene(m_mapScene);
    RoomProperties *rp = new RoomProperties(this);
    ui->horizontalLayout->insertWidget(0, rp, 0 );
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    m_mapScene->addItem(new Room(Room::Lava));
    connect(rp, SIGNAL(roomTypeChanged(int)), m_mapScene, SLOT(setCurrentRoomType(int)));
    connect(rp, SIGNAL(roomFlagsChanged(Room::Flags)), m_mapScene, SLOT(setCurrentRoomFlags(Room::Flags)));
    connect(rp, SIGNAL(roomShortDescriptionChanged(QString)), m_mapScene, SLOT(setCurrentRoomShortDescription(QString)));
    connect(rp, SIGNAL(roomLongDescriptionChanged(QString)), m_mapScene, SLOT(setCurrentRoomLongDescription(QString)));
    connect(m_mapScene, SIGNAL(currentRoomChanged(Room*)), rp, SLOT(populateControls(Room*)));
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

void MainWindow::newFile()
{

}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QString(), tr("LispMud Zone files (*.lzon)"));
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    QString(), tr("LispMud Zone files (*.lzon)"));

    if ( fileName.isEmpty() ) // User pressed Cancel button.
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){ // Standard Qt way to open files.
        QMessageBox::warning(this,QString("Save file error"),
                             QString("Can't open file\"%1\".\nPlease try saving it again").arg(fileName));
        return;
    }
    file.write(m_mapScene->zoneText().toUtf8());
    file.close();
}
