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

#ifndef ROOMPROPERTIES_H
#define ROOMPROPERTIES_H

#include <QGroupBox>

#include "room.h"

namespace Ui {
    class RoomProperties;
}

class RoomProperties : public QGroupBox {
    Q_OBJECT
public:
    RoomProperties(QWidget *parent = 0);
    ~RoomProperties();

    void setRoomType(int type);
    void setRoomFlags(Room::Flags flags);
    void setRoomShortDescription(QString);
    void setRoomLongDescription(QString);

public slots:
    void changeRoomType(int type);
    void changeRoomFlags();
    void changeRoomShortDescription(QString);
    void changeRoomLongDescription();

    void populateControls(Room *);

signals:
    void roomTypeChanged(int type);
    void roomFlagsChanged(Room::Flags flags);
    void roomShortDescriptionChanged(QString);
    void roomLongDescriptionChanged(QString);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomProperties *ui;
};

#endif // ROOMPROPERTIES_H
