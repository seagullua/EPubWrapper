#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Utils/CreateIcon.h"
#include <QDebug>

static const QString APPLICATION_NAME(QObject::tr("EPub To APK"));

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->conversionForm->layout()->


    selectEpub("E:\\downloads\\moby-dick-20120118.epub");
}

MainWindow::~MainWindow()
{
    delete ui;
}










void MainWindow::selectEpub(QString epub_file)
{
    this->setWindowTitle(APPLICATION_NAME + " - " + epub_file);
}


