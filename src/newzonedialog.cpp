#include "newzonedialog.h"
#include "ui_newzonedialog.h"

NewZoneDialog::NewZoneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewZoneDialog)
{
    ui->setupUi(this);
}

NewZoneDialog::~NewZoneDialog()
{
    delete ui;
}

void NewZoneDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

int NewZoneDialog::sizeX()
{
    return ui->spinBoxSizeX->value();
}

void NewZoneDialog::setSizeX(int X)
{
   ui->spinBoxSizeX->setValue(X);
}

int NewZoneDialog::sizeY()
{
    return ui->spinBoxSizeY->value();
}

void NewZoneDialog::setSizeY(int Y)
{
    ui->spinBoxSizeY->setValue(Y);
}

QString NewZoneDialog::name()
{
    return ui->lineEditName->text();
}

void NewZoneDialog::setName(QString name)
{
    ui->lineEditName->setText(name);
}
