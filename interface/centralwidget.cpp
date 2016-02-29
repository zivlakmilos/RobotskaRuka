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

CentralWidget::CentralWidget(QextSerialPort *port, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CentralWidget)
{
    ui->setupUi(this);

    this->port = port;

    this->timer = new QTimer(this);
    this->timer->setInterval(10);

    this->useCv = false;
    
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

    connect(this->timer, SIGNAL(timeout()),
            this, SLOT(render()));

    timer->start();
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

void CentralWidget::render()
{
}
