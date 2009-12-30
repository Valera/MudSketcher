#ifndef ROOMPROPERTIES_H
#define ROOMPROPERTIES_H

#include <QGroupBox>

namespace Ui {
    class RoomProperties;
}

class RoomProperties : public QGroupBox {
    Q_OBJECT
public:
    RoomProperties(QWidget *parent = 0);
    ~RoomProperties();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoomProperties *ui;
};

#endif // ROOMPROPERTIES_H
