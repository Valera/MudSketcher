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

public slots:
    void changeRoomType(QString type);

signals:
    void roomTypeChanged(int type);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomProperties *ui;
};

#endif // ROOMPROPERTIES_H
