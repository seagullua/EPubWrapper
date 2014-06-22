#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&_compiler, SIGNAL(logMessage(QString)), this, SLOT(onLog(QString)));
    connect(&_compiler, SIGNAL(errorMessage(QString)), this, SLOT(onError(QString)));
    connect(&_compiler, SIGNAL(warningMessage(QString)), this, SLOT(onWarning(QString)));
    connect(&_compiler, SIGNAL(finished(bool,QString)), this, SLOT(onFinish(bool,QString)));
    connect(ui->start, SIGNAL(clicked()), this, SLOT(onStart()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLog(QString text)
{
    ui->log->append(text);
}

void MainWindow::onWarning(QString text)
{
    ui->log->append(QString("<font color=\"#e9db00\">%1</font>").arg(text));
}

void MainWindow::onError(QString text)
{
    ui->log->append(QString("<font color=\"red\">%1</font>").arg(text));
}

void MainWindow::onFinish(bool success, QString text)
{
    if(success)
    {
        ui->log->append(tr("<font color=\"green\">BUILD SUCCESSFULL</font>"));
    }
    else
    {
        ui->log->append(tr("<font color=\"red\">BUILD FAILED: %1</font>").arg(text));
    }
}

void MainWindow::onStart()
{
    _compiler.setAndroidSdkPath("C:\\Program Files (x86)\\Android\\android-sdk");
    _compiler.setAntPath("C:\\ant\\bin");
    _compiler.setBookName(ui->bookName->text());
    _compiler.setCoverImageName("");
    _compiler.setInputEpub("E:\\downloads\\moby-dick-20120118.epub");
    _compiler.setJdkPath("C:\\Program Files\\Java\\jdk1.7.0_10\\bin");
    _compiler.setOutputApkName("E:\\mobidick\\mobidick.apk");
    _compiler.setPackageName("book.mobidick");
    _compiler.setTemplatePath("F:\\GitHub\\Wrapper");

    _compiler.startCompilation();
}
