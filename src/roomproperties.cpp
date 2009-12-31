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
