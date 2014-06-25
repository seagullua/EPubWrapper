#include "ConversionWidget.h"
#include "ui_ConversionWidget.h"
#include <QDir>


ConversionWidget::ConversionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConversionWidget)
{
    ui->setupUi(this);
}

void ConversionWidget::onLog(QString text)
{
    ui->log->append(QString("<font color=\"black\">%1</font>").arg(text));
}

void ConversionWidget::onWarning(QString text)
{
    ui->log->append(QString("<font color=\"#e9db00\">%1</font>").arg(text));
}

void ConversionWidget::onError(QString text)
{
    ui->log->append(QString("<font color=\"red\">%1</font>").arg(text));
}

void ConversionWidget::onFinish(bool success, QString text)
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
void ConversionWidget::setBookName(QString book_name)
{
    _book_name = book_name;
}

void ConversionWidget::setPackageName(QString package_name)
{
    _package_name = package_name;
}

void ConversionWidget::setImage(QPixmap image)
{
    _has_cover = true;
    _cover = image;
}

void ConversionWidget::setInputEpub(QString epub)
{
    _epub_file = epub;
}

void ConversionWidget::setOutputPath(QString output)
{
    _output_path = output;
}

void ConversionWidget::useDefaultImage()
{
    _has_cover = false;
}

void ConversionWidget::startConversion()
{
    ui->log->clear();
    AndroidCompilePtr compiler(new AndroidCompile);

    connect(&*compiler, SIGNAL(logMessage(QString)), this, SLOT(onLog(QString)));
    connect(&*compiler, SIGNAL(errorMessage(QString)), this, SLOT(onError(QString)));
    connect(&*compiler, SIGNAL(warningMessage(QString)), this, SLOT(onWarning(QString)));
    connect(&*compiler, SIGNAL(finished(bool,QString)), this, SLOT(onFinish(bool,QString)));

    connect(&*compiler, SIGNAL(progress(int,int)), this, SLOT(onProgress(int,int)));


    compiler->setAndroidSdkPath(getProjectDir("external/android-sdk"));
    compiler->setAntPath(getProjectDir("external/ant/bin"));
    compiler->setBookName(_book_name);
    if(_has_cover)
    {
        compiler->setCoverImage(_cover);
    }

    compiler->setInputEpub(_epub_file);
    compiler->setJdkPath(getProjectDir("external/jdk"));
    compiler->setOutputApkName(_output_path);
    compiler->setPackageName(_package_name);
    compiler->setTemplatePath(getProjectDir("external/wrapper-template"));

    compiler->startCompilationAsync();

    if(!_compiler.isNull())
    {
        _compiler->cancel();
        _compiler->waitUntilCanceled();
    }
    _compiler = compiler;
}

QString ConversionWidget::getProjectDir(QString path)
{
    QString input = QDir::toNativeSeparators(path);
    QString res = QDir(input).absolutePath();
    return res;
}

void ConversionWidget::onProgress(int steps_made, int steps)
{
    ui->compileProgress->setMaximum(steps);
    ui->compileProgress->setValue(steps_made);
}

ConversionWidget::~ConversionWidget()
{
    delete ui;
}
