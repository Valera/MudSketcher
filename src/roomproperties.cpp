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
    connect(ui->lineEditDescription, SIGNAL(textEdited(QString)), this, SLOT(changeRoomShortDescription(QString)));
    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(changeRoomLongDescription()));
    setDisabled(true);
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

void RoomProperties::setRoomType(int type)
{
    ui->comboBox->setCurrentIndex(type);
}

void RoomProperties::setRoomFlags(Room::Flags flags)
{
    bool b;
    b = flags.testFlag(Room::Dark);
    ui->checkBoxDark->setChecked(b);
    b = flags.testFlag(Room::NoMob);
    ui->checkBoxNoMob->setChecked(b);
    b = flags.testFlag(Room::Peacefull);
    ui->checkBoxPeace->setChecked(b);
    b = flags.testFlag(Room::Service);
    ui->checkBoxService->setChecked(b);
    b = flags.testFlag(Room::Tunnel);
    ui->checkBoxTunnel->setChecked(b);
}

void RoomProperties::setRoomShortDescription(QString str)
{
    ui->lineEditDescription->setText(str);
}

void RoomProperties::setRoomLongDescription(QString str)
{
    ui->plainTextEdit->setPlainText(str);
}

void RoomProperties::changeRoomType(int type)
{
    emit roomTypeChanged(Room::RoomType(type));
}

void RoomProperties::populateControls(Room *r)
{
    if(!r){
        setDisabled(true);
        return;
    }else{
        setDisabled(false);
    }
    setRoomFlags(r->roomFlags());
    setRoomType(r->roomType());
    setRoomShortDescription(r->roomShortDescription());
    setRoomLongDescription(r->roomLongDescription());
}

void RoomProperties::changeRoomFlags()
{
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

void RoomProperties::changeRoomLongDescription()
{
    //ui->plainTextEdit->toPlainText()
    emit roomLongDescriptionChanged(ui->plainTextEdit->toPlainText());
}
