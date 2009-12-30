#include "roomproperties.h"
#include "ui_roomproperties.h"

#include <QDebug>

RoomProperties::RoomProperties(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::RoomProperties)
{
    ui->setupUi(this);
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

void RoomProperties::changeRoomType(QString type)
{
    if ( type == QString::fromUtf8("Лес"))
        emit roomTypeChanged(1);
}
