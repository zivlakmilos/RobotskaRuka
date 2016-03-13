#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile fileStylesheet("QTDark.stylesheet");
    fileStylesheet.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(fileStylesheet.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();

    return a.exec();
}
