#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MapScene;
class RoomProperties;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newFile();
    void open();
    void save();
    void editZoneProperties();
    //void exit();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    MapScene * m_mapScene;
    RoomProperties *m_roomProperties;
    QAction *m_actionZoneProperties;
};

#endif // MAINWINDOW_H
