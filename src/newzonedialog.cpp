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
