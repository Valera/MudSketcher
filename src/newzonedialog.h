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

#ifndef NEWZONEDIALOG_H
#define NEWZONEDIALOG_H

#include <QDialog>

namespace Ui {
    class NewZoneDialog;
}

/* UI class for creation of new zone.
   Use setSizeX, setSizeY, setName for setting default values before showing dialog.
   Use sizeX, sizeY, name for getting new values after executiong of dialog.
*/

class NewZoneDialog : public QDialog {
    Q_OBJECT
public:
    NewZoneDialog(QWidget *parent = 0);
    ~NewZoneDialog();

    int sizeX();
    void setSizeX(int X);

    int sizeY();
    void setSizeY(int Y);

    QString name();
    void setName(QString name);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::NewZoneDialog *ui;
};

#endif // NEWZONEDIALOG_H
