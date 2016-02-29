#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QTabWidget>

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

    cv::Mat matOriginal;
    cv::Mat matOfilter;
    QImage *original;
    QImage *filter;

    QByteArray data;

    bool useCv;

private slots:
    void robotStateChanged();
    void render();
};

#endif // CENTRALWIDGET_H
