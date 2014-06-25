#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Utils/CreateIcon.h"
#include <QDebug>
#include <QDir>
#include "Utils/EpubInfo.h"
#include "Utils/Naming.h"
#include <QDebug>

static const QSize COVER_PREVIEW(150, 200);
static const QString APPLICATION_NAME(QObject::tr("EPub To APK"));

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&_compiler, SIGNAL(logMessage(QString)), this, SLOT(onLog(QString)));
    connect(&_compiler, SIGNAL(errorMessage(QString)), this, SLOT(onError(QString)));
    connect(&_compiler, SIGNAL(warningMessage(QString)), this, SLOT(onWarning(QString)));
    connect(&_compiler, SIGNAL(finished(bool,QString)), this, SLOT(onFinish(bool,QString)));
    //connect(ui->start, SIGNAL(clicked()), this, SLOT(onStart()));
    ui->coverPreview->setMinimumSize(COVER_PREVIEW);
    this->setWindowTitle(APPLICATION_NAME);

    connect(ui->bookName, SIGNAL(textChanged(QString)), this, SLOT(updatePackageName(QString)));

    selectEpub("D:\\epubs\\ostrov_sokrovish_.epub");
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

void MainWindow::updatePackageName(QString new_name)
{
    QString book_name = new_name;
    QString latin = Naming::createLatinName(book_name);
    //qDebug() << book_name << latin;
    QString package_name = "book." + Naming::forPackageName(latin);
    ui->androidPackage->setText(package_name);
}

void MainWindow::onLog(QString text)
{
    //ui->log->append(text);
}

void MainWindow::onWarning(QString text)
{
    //ui->log->append(QString("<font color=\"#e9db00\">%1</font>").arg(text));
}

void MainWindow::onError(QString text)
{
    //ui->log->append(QString("<font color=\"red\">%1</font>").arg(text));
}

void MainWindow::onFinish(bool success, QString text)
{
    if(success)
    {
        //ui->log->append(tr("<font color=\"green\">BUILD SUCCESSFULL</font>"));
    }
    else
    {
        //ui->log->append(tr("<font color=\"red\">BUILD FAILED: %1</font>").arg(text));
    }
}

void MainWindow::selectEpub(QString epub_file)
{
    this->setWindowTitle(APPLICATION_NAME + " - " + epub_file);
    _epub_file = epub_file;
    EpubInfo info(epub_file);
    _has_cover = false;
    if(info.hasCover())
    {
        ui->bookName->setText(info.getBookName());
        _has_cover = true;
        _cover = info.getCover();
        QPixmap thumb = _cover.scaled(COVER_PREVIEW, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        //qDebug() << ui->coverPreview->size();
        ui->coverPreview->setPixmap(thumb);
        ui->coverImageFile->setText(tr("(default)"));
    }
    else
    {
        ui->coverImageFile->setText(tr("(no cover)"));
    }
    ui->saveToPath->setText(epub_file+".apk");
}

void MainWindow::onStart()
{

    _compiler.setAndroidSdkPath(getProjectDir("external/android-sdk"));
    _compiler.setAntPath(getProjectDir("external/ant/bin"));
    _compiler.setBookName(ui->bookName->text());
    if(_has_cover)
    {
        _compiler.setCoverImage(_cover);
    }

    _compiler.setInputEpub(_epub_file);
    _compiler.setJdkPath(getProjectDir("external/jdk"));
    _compiler.setOutputApkName(ui->saveToPath->text());
    _compiler.setPackageName(ui->androidPackage->text());
    _compiler.setTemplatePath(getProjectDir("external/wrapper-template"));

    _compiler.startCompilation();
}
