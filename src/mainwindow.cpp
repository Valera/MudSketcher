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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRectF>
#include <QPointF>
#include <QFileDialog>
#include <QMessageBox>
#include <QCommonStyle>

#include <QDebug>

#include "room.h"
#include "mapscene.h"
#include "roomproperties.h"
#include "newzonedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Assign icons to actions.
    QCommonStyle style;
    ui->actionNew ->setIcon(style.standardIcon(QStyle::SP_FileIcon));
    ui->actionOpen->setIcon(style.standardIcon(QStyle::SP_DialogOpenButton));
    ui->actionSave->setIcon(style.standardIcon(QStyle::SP_DialogSaveButton));

    // Connect menu entries.
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // Adding actions to toolbar.
    ui->mainToolBar->addAction(ui->actionNew);
    ui->mainToolBar->addAction(ui->actionOpen);
    ui->mainToolBar->addAction(ui->actionSave);

    m_roomProperties = new RoomProperties(this);
    ui->horizontalLayout->insertWidget(0, m_roomProperties, 0 );

    m_mapScene = 0;
    ui->actionSave->setEnabled(false);

    // Now opening zone files doesn't work. :(
    ui->actionOpen->setEnabled(false);

    m_actionZoneProperties
            = new QAction(style.standardIcon(QStyle::SP_MessageBoxQuestion), QString("Edit zone"), this);
    connect(m_actionZoneProperties, SIGNAL(triggered()), this, SLOT(editZoneProperties()));
    ui->mainToolBar->addAction(m_actionZoneProperties);
    m_actionZoneProperties->setEnabled(false);
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
    NewZoneDialog dialog(this);
    dialog.exec();
    if(dialog.result() == QDialog::Rejected) // If user pressed Cancel, do nothing.
        return;

    // Create map scene and connect its signals to room properties panel and vise versa.
    m_mapScene = new MapScene(this, dialog.sizeX(), dialog.sizeY(), dialog.name());
    ui->graphicsView->setScene(m_mapScene);
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    //m_mapScene->addItem(new Room(Room::Lava));
    connect(m_roomProperties, SIGNAL(roomTypeChanged(int)), m_mapScene, SLOT(setCurrentRoomType(int)));
    connect(m_roomProperties, SIGNAL(roomFlagsChanged(Room::Flags)), m_mapScene, SLOT(setCurrentRoomFlags(Room::Flags)));
    connect(m_roomProperties, SIGNAL(roomShortDescriptionChanged(QString)), m_mapScene, SLOT(setCurrentRoomShortDescription(QString)));
    connect(m_roomProperties, SIGNAL(roomLongDescriptionChanged(QString)), m_mapScene, SLOT(setCurrentRoomLongDescription(QString)));
    connect(m_mapScene, SIGNAL(currentRoomChanged(Room*)), m_roomProperties, SLOT(populateControls(Room*)));
    ui->actionSave->setEnabled(true);
    m_actionZoneProperties->setEnabled(true);
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

void MainWindow::editZoneProperties()
{
    NewZoneDialog dialog(this);
    // Populate dialog with old data...
    dialog.setSizeX(m_mapScene->zoneWidth());
    dialog.setSizeY(m_mapScene->zoneHeight());
    dialog.setName(m_mapScene->zoneName());
    dialog.exec();
    if(dialog.result() == QDialog::Rejected) // If user pressed Cancel, do nothing.
        return;
    // Get updated data to Scene...
    m_mapScene->setZoneHeight(dialog.sizeY());
    m_mapScene->setZoneWidth(dialog.sizeX());
    m_mapScene->setZoneName(dialog.name());
    // Force redraw.
    m_mapScene->update();
}
