#ifndef NEWZONEDIALOG_H
#define NEWZONEDIALOG_H

#include <QDialog>

namespace Ui {
    class NewZoneDialog;
}

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
