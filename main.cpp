#include <QApplication>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":/default");
    a.installTranslator(&translator);

    MainWindow w;
    w.setFixedSize(w.size());
    w.show();

    return a.exec();
}
