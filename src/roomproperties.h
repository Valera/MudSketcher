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
