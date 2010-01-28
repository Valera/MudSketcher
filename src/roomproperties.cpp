#include "roomproperties.h"
#include "ui_roomproperties.h"

#include <QDebug>

#include "room.h"

RoomProperties::RoomProperties(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::RoomProperties)
{
    ui->setupUi(this);
    for(int e = Room::Hills; e < Room::Unknown; e++)
        ui->comboBox->addItem(Room::roomTypeName(Room::RoomType(e)), e);
    connect(ui->checkBoxDark, SIGNAL(stateChanged(int)), this, SLOT(changeRoomFlags()));
    connect(ui->checkBoxNoMob, SIGNAL(stateChanged(int)), this, SLOT(changeRoomFlags()));
    connect(ui->checkBoxPeace, SIGNAL(stateChanged(int)), this, SLOT(changeRoomFlags()));
    connect(ui->checkBoxService, SIGNAL(stateChanged(int)), this, SLOT(changeRoomFlags()));
    connect(ui->checkBoxTunnel, SIGNAL(stateChanged(int)), this, SLOT(changeRoomFlags()));
    connect(ui->lineEditDescription, SIGNAL(textEdited(QString)), this, SLOT(roomShortDescriptionChanged(QString)));
}

RoomProperties::~RoomProperties()
{
    delete ui;
}

void RoomProperties::changeEvent(QEvent *e)
{
    QGroupBox::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void RoomProperties::changeRoomType(int type)
{
    emit roomTypeChanged(Room::RoomType(type));
}

void RoomProperties::changeRoomFlags()
{
    /*qDebug() << "Hello world!";
    qDebug() << ui->checkBoxDark->isChecked();
    qDebug() << ui->checkBoxNoMob->isChecked();
    qDebug() << ui->checkBoxPeace->isChecked();
    qDebug() << ui->checkBoxService->isChecked();
    qDebug() << ui->checkBoxTunnel->isChecked();
    */

    Room::Flags flags;
    if (ui->checkBoxDark->isChecked()) flags |= Room::Dark;
    if (ui->checkBoxNoMob->isChecked()) flags |= Room::NoMob;
    if (ui->checkBoxPeace->isChecked()) flags |= Room::Peacefull;
    if (ui->checkBoxService->isChecked()) flags |= Room::Service;
    if (ui->checkBoxTunnel->isChecked()) flags |= Room::Tunnel;
    //qDebug() << flags;

    emit roomFlagsChanged(flags);
}

void RoomProperties::changeRoomShortDescription(QString str)
{
    emit roomShortDescriptionChanged(str);
}

void RoomProperties::changeRoomLongDescription(QString str)
{
    emit roomLongDescriptionChanged(str);
}
