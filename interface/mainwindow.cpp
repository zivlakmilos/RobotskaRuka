#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QMessageBox>
#include <QtGui>

#include <QtExtSerialPort/qextserialport.h>
#include <QtExtSerialPort/qextserialenumerator.h>

#include "centralwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Robotksa ruka"));

    ports = QextSerialEnumerator::getPorts();

    port = new QextSerialPort();
    port->setBaudRate(BAUD9600);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    port->setParity(PAR_NONE);
    port->setFlowControl(FLOW_OFF);

    connected = false;

//    foreach (QextPortInfo info, ports)
//    {
//    }

    menuPort = new QMenu("&Port", this);
    menuBar()->addMenu(menuPort);

    for(int i = 0; i < ports.length(); i++)
    {
        actionPorts.append(new QAction(ports[i].portName, this));
        menuPort->addAction(actionPorts[i]);
        connect(actionPorts[i], SIGNAL(triggered(bool)), this, SLOT(portSelected()));
    }

    actionAbout = new QAction(tr("&O programu"), this);
    menuBar()->addAction(actionAbout);

    actionExit = new QAction(tr("&Izlaz"), this);
    menuBar()->addAction(actionExit);

    lblPortStatus = new QLabel(tr("Nema konekcije na robota"), this);
    statusBar()->addWidget(lblPortStatus);

    connect(actionAbout, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(port, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

MainWindow::~MainWindow()
{
    if(port->isOpen())
        port->close();
    delete port;
    delete ui;
}

void MainWindow::portSelected()
{
    if(connected)
        return;

    QString portName = ((QAction *)sender())->text();

    if(port->isOpen())
        port->close();

    port->setPortName(portName);
    port->open(QIODevice::ReadWrite);
}

void MainWindow::readyRead()
{
    if(connected)
        return;

    QByteArray data;

    data = port->readAll();

    if(data.data()[0] == MAGIC_NUMBER)
    {
        this->connected = true;

        this->centralWidget = new CentralWidget(port, this);
        this->setCentralWidget(centralWidget);

        this->lblPortStatus->setText(tr("Robot konektovan na %1").arg(port->portName()));
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("Robotska ruka"),
                       tr("Program za upravljanje robotskom rukom.<br />"
                          "Osnovna Skola \"Jovan Jovanovic Zmaj\" Sremska kamenica.<br /><br />"
                          "<div align=\"right\"><b>"
                          "&copy; Milos Zivlak 2016<br />"
                          "zivlakmilos@gmail.com"
                          "</b></div>"));
}
