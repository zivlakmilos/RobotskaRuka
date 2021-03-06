#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QTabWidget>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class HandGesture;

class QextSerialPort;

namespace Ui {
class CentralWidget;
}

class CentralWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QextSerialPort *port, QWidget *parent = 0);
    ~CentralWidget();

private:
    Ui::CentralWidget *ui;

    QextSerialPort *port;

    QTimer *timer;

    QByteArray data;

    HandGesture *handGesture;

    bool cvIsOk;
    bool colorIsPicked;
    int timerMilisec;

    int rot;
    int seg1;
    int seg2;
    int seg3;

private slots:
    void robotStateChanged();
    void tabChanged(int index);
    void cvOptionsChanged();
    void render();
};

#endif // CENTRALWIDGET_H
