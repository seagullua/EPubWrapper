#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qt_localization;

    qt_localization.load("uk", ":/translation");
    a.installTranslator(&qt_localization);

    MainWindow w;
    w.show();
    
    return a.exec();
}
