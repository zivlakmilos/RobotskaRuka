#include "centralwidget.h"
#include "ui_centralwidget.h"

#include <QMessageBox>
#include <QtCore>

#include <QtExtSerialPort/qextserialport.h>

/* Za delay */
#include <QThread>
class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};
/* Za delay */

using namespace cv;

CentralWidget::CentralWidget(QextSerialPort *port, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CentralWidget)
{
    ui->setupUi(this);

    this->port = port;

    this->timer = new QTimer(this);
    this->timer->setInterval(10);

    this->capture = VideoCapture(0);

    lowH = 170;
    highH = 179;
    lowS = 150;
    highS = 255;
    lowV = 60;
    highV = 255;

    this->x = -1;
    this->y = -1;
    
    connect(ui->dialRot, SIGNAL(valueChanged(int)),
            ui->sbRot, SLOT(setValue(int)));
    connect(ui->sbRot, SIGNAL(valueChanged(int)),
            ui->dialRot, SLOT(setValue(int)));
    connect(ui->hsSeg1, SIGNAL(valueChanged(int)),
            ui->sbSeg1, SLOT(setValue(int)));
    connect(ui->sbSeg1, SIGNAL(valueChanged(int)),
            ui->hsSeg1, SLOT(setValue(int)));
    connect(ui->hsSeg2, SIGNAL(valueChanged(int)),
            ui->sbSeg2, SLOT(setValue(int)));
    connect(ui->sbSeg2, SIGNAL(valueChanged(int)),
            ui->hsSeg2, SLOT(setValue(int)));
    connect(ui->hsSeg3, SIGNAL(valueChanged(int)),
            ui->sbSeg3, SLOT(setValue(int)));
    connect(ui->sbSeg3, SIGNAL(valueChanged(int)),
            ui->hsSeg3, SLOT(setValue(int)));
    connect(ui->hsHvat, SIGNAL(valueChanged(int)),
            ui->sbHvat, SLOT(setValue(int)));
    connect(ui->sbHvat, SIGNAL(valueChanged(int)),
            ui->hsHvat, SLOT(setValue(int)));

    connect(ui->sbRot, SIGNAL(valueChanged(int)),
            this, SLOT(robotStateChanged()));
    connect(ui->sbSeg1, SIGNAL(valueChanged(int)),
            this, SLOT(robotStateChanged()));
    connect(ui->sbSeg2, SIGNAL(valueChanged(int)),
            this, SLOT(robotStateChanged()));
    connect(ui->sbSeg3, SIGNAL(valueChanged(int)),
            this, SLOT(robotStateChanged()));
    connect(ui->sbHvat, SIGNAL(valueChanged(int)),
            this, SLOT(robotStateChanged()));

    connect(ui->sbHH, SIGNAL(valueChanged(int)),
            ui->hsHH, SLOT(setValue(int)));
    connect(ui->sbHL, SIGNAL(valueChanged(int)),
            ui->hsHL, SLOT(setValue(int)));
    connect(ui->sbSH, SIGNAL(valueChanged(int)),
            ui->hsSH, SLOT(setValue(int)));
    connect(ui->sbSL, SIGNAL(valueChanged(int)),
            ui->hsSL, SLOT(setValue(int)));
    connect(ui->sbVH, SIGNAL(valueChanged(int)),
            ui->hsVH, SLOT(setValue(int)));
    connect(ui->sbVL, SIGNAL(valueChanged(int)),
            ui->hsVL, SLOT(setValue(int)));
    connect(ui->hsHH, SIGNAL(valueChanged(int)),
            ui->sbHH, SLOT(setValue(int)));
    connect(ui->hsHL, SIGNAL(valueChanged(int)),
            ui->sbHL, SLOT(setValue(int)));
    connect(ui->hsSH, SIGNAL(valueChanged(int)),
            ui->sbSH, SLOT(setValue(int)));
    connect(ui->hsSL, SIGNAL(valueChanged(int)),
            ui->sbSL, SLOT(setValue(int)));
    connect(ui->hsVH, SIGNAL(valueChanged(int)),
            ui->sbVH, SLOT(setValue(int)));
    connect(ui->hsVL, SIGNAL(valueChanged(int)),
            ui->sbVL, SLOT(setValue(int)));

    connect(ui->sbHH, SIGNAL(valueChanged(int)),
            this, SLOT(cvOptionsChanged()));
    connect(ui->sbHL, SIGNAL(valueChanged(int)),
            this, SLOT(cvOptionsChanged()));
    connect(ui->sbSH, SIGNAL(valueChanged(int)),
            this, SLOT(cvOptionsChanged()));
    connect(ui->sbSL, SIGNAL(valueChanged(int)),
            this, SLOT(cvOptionsChanged()));
    connect(ui->sbVH, SIGNAL(valueChanged(int)),
            this, SLOT(cvOptionsChanged()));
    connect(ui->sbVL, SIGNAL(valueChanged(int)),
            this, SLOT(cvOptionsChanged()));

    ui->sbHH->setValue(highH);
    ui->sbHL->setValue(lowH);
    ui->sbSH->setValue(highS);
    ui->sbSL->setValue(lowS);
    ui->sbVH->setValue(highV);
    ui->sbVL->setValue(lowV);

    connect(this, SIGNAL(currentChanged(int)),
            this, SLOT(tabChanged(int)));

    connect(this->timer, SIGNAL(timeout()),
            this, SLOT(render()));
}

CentralWidget::~CentralWidget()
{
    delete ui;
}

void CentralWidget::robotStateChanged()
{
    if(port->isOpen())
    {
//        QByteArray data;
//        QString name = sender()->objectName();

//        if(name == "sbRot")
//            data.append('r');
//        else if(name == "sbSeg1")
//            data.append('1');
//        else if(name == "sbSeg2")
//            data.append('2');
//        else if(name == "sbSeg3")
//            data.append('3');
//        else if(name == "sbHvat")
//            data.append('h');

//        data.append(((QSpinBox *)sender())->value());

        data.clear();
        data.append(ui->sbRot->value());
        data.append(ui->sbSeg1->value());
        data.append(ui->sbSeg2->value());
        data.append(ui->sbSeg3->value());
        data.append(ui->sbHvat->value());

        this->port->write(data);
        this->port->flush();
        Sleeper::msleep(50);
    } else
    {
        QMessageBox::warning(this, tr("Robotska ruka"),
                             tr("Doslo je do greske prilikom komunikacije sa robotom.<br />"
                                "Proverite da li je robot dobro povezan, a zatim ponovo pokrenite program.<br /><br />"
                                "Ako ponovo ne bude radilo, obratite se na mail koji mozete procitati u \"O programu\"."),
                             QMessageBox::Ok);
    }
}

void CentralWidget::tabChanged(int index)
{
    if(index == 1)
        this->timer->start();
    else
        this->timer->stop();
}

void CentralWidget::cvOptionsChanged()
{
    this->highH = ui->sbHH->value();
    this->lowH = ui->sbHL->value();
    this->highS = ui->sbSH->value();
    this->lowS = ui->sbSL->value();
    this->highV = ui->sbVH->value();
    this->lowV = ui->sbVL->value();
}

void CentralWidget::render()
{
    if(capture.isOpened())
    {
        Mat matOriginal;
        Mat matHsv;
        Mat matFilter;
        Mat matTmp;
        Mat matLines;

        QImage original;
        QImage filter;

        if(!capture.read(matOriginal))
            return;

        cvtColor(matOriginal, matHsv, COLOR_BGR2HSV);
        inRange(matHsv, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), matFilter);

        erode(matFilter, matFilter, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate(matFilter, matFilter, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

        dilate(matFilter, matFilter, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        erode(matFilter, matFilter, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

        capture.read(matTmp);

        matLines = Mat::zeros(matTmp.size(), CV_8UC3);

        Moments oMoments = moments(matFilter);

        double m01 = oMoments.m01;
        double m10 = oMoments.m10;
        double area = oMoments.m00;

        if(area > 10000)
        {
            int posX = m10 / area;
            int posY = m01 / area;

            if(this->x >= 0 && this->y >= 0 && posX >= 0 && posY >= 0)
            {
                line(matLines, Point(posX, posY), Point(this->x, this->y), Scalar(0, 255, 255), 2);

                /*
                * ToDo:
                *  Send to Arduino
                *  (cakculate and change value for Tab1 elements)
                */
                ui->sbRot->setValue((posX * 180) / matOriginal.rows);
                qDebug() << ui->sbRot->value();
            }

            this->x = posX;
            this->y = posY;
        }

        matOriginal = matOriginal + matLines;

        switch(matOriginal.type())
        {
            case CV_8UC4:
                original = QImage(matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB32);
                break;
            case CV_8UC3:
                original = QImage(matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
                original.rgbSwapped();
                break;
            case CV_8UC1:
                static QVector<QRgb> colorTable;
                    for(int i = 0; i < 256; i++)
                        colorTable.push_back(qRgb(i, i, i));
                original = QImage(matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_Indexed8);
                original.setColorTable(colorTable);
                break;
        }
        switch(matFilter.type())
        {
            case CV_8UC4:
                filter = QImage(matFilter.data, matFilter.cols, matFilter.rows, matFilter.step, QImage::Format_RGB32);
                break;
            case CV_8UC3:
                filter = QImage(matFilter.data, matFilter.cols, matFilter.rows, matFilter.step, QImage::Format_RGB888);
                filter.rgbSwapped();
                break;
            case CV_8UC1:
                static QVector<QRgb> colorTable;
                    for(int i = 0; i < 256; i++)
                        colorTable.push_back(qRgb(i, i, i));
                filter = QImage(matFilter.data, matFilter.cols, matFilter.rows, matFilter.step, QImage::Format_Indexed8);
                filter.setColorTable(colorTable);
                break;
        }

        original = original.scaled(ui->imgOriginal->width(),
                                   ui->imgOriginal->height(),
                                   Qt::KeepAspectRatio);
        filter = filter.scaled(ui->imgFilter->width(),
                               ui->imgFilter->height(),
                               Qt::KeepAspectRatio);

        ui->imgOriginal->setPixmap(QPixmap::fromImage(original));
        ui->imgFilter->setPixmap(QPixmap::fromImage(filter));
    }
}
