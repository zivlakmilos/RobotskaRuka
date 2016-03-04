#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QTabWidget>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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

    cv::VideoCapture capture;

    QByteArray data;

    int lowH;
    int highH;
    int lowS;
    int highS;
    int lowV;
    int highV;

    int x;
    int y;

private slots:
    void robotStateChanged();
    void tabChanged(int index);
    void cvOptionsChanged();
    void render();
};

#endif // CENTRALWIDGET_H
