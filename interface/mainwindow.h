#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;

class QextSerialPort;
class QextPortInfo;

class CentralWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMenu *menuPort;

    QList<QAction *> actionPorts;
    QAction *actionAbout;
    QAction *actionExit;

    QextSerialPort *port;
    QList<QextPortInfo> ports;

    QLabel *lblPortStatus;

    CentralWidget *centralWidget;

    bool connected;

    enum { MAGIC_NUMBER = 0x38 };

private slots:
    void portSelected();
    void readyRead();
    void about();
};

#endif // MAINWINDOW_H
