#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
static const QString REG_ICON = "icon";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qt_localization;

    qt_localization.load("uk", ":/translation");
    a.installTranslator(&qt_localization);

    MainWindow::registerQuickAction();

    QStringList arguments = QCoreApplication::arguments();
    if(arguments.size() >= 2)
    {
        QString arg = arguments.at(1);
        if(arg == REG_ICON)
        {
            return 0;
        }
    }


    MainWindow w;
    w.show();
    
    return a.exec();
}
