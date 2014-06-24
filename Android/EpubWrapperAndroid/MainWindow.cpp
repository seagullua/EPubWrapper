#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Utils/CreateIcon.h"
#include <QDebug>
#include <QDir>
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

QString MainWindow::getProjectDir(QString path)
{
    QString input = QDir::toNativeSeparators(path);
    QString res = QDir(input).absolutePath();
    return res;
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

    _compiler.setAndroidSdkPath(getProjectDir("external/android-sdk"));
    _compiler.setAntPath(getProjectDir("external/ant/bin"));
    _compiler.setBookName(ui->bookName->text());
    _compiler.setCoverImageName("");
    _compiler.setInputEpub("E:\\downloads\\moby-dick-20120118.epub");
    _compiler.setJdkPath(getProjectDir("external/jdk"));
    _compiler.setOutputApkName("E:\\mobidick.apk");
    _compiler.setPackageName("book.lady_susan");
    _compiler.setTemplatePath(getProjectDir("external/wrapper-template"));

    _compiler.startCompilation();
}
