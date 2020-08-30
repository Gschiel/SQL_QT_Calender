#include "mainwindow.h"
#include "filestream.h"
#include "filter.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(611, 578);
    w.show();
    return a.exec();
}
