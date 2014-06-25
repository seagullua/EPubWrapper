#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include "Utils/EpubInfo.h"
#include <QMessageBox>

static const QString APPLICATION_NAME(QObject::tr("EPub To APK"));

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->formPreview, SIGNAL(startConversion()), this, SLOT(startConversion()));
    connect(ui->formCoversion, SIGNAL(finished(bool,QString)), this, SLOT(conversionFinished(bool,QString)));
    connect(ui->formFailed, SIGNAL(tryAgain()), this, SLOT(tryAgain()));
    connect(ui->formSuccess, SIGNAL(newEpub()), this, SLOT(newEpub()));
    connect(ui->formSuccess, SIGNAL(openFolder()), this, SLOT(openApkInFolder()));

    _forms[FormConversion] = ui->formCoversion;
    _forms[FormFailed] = ui->formFailed;
    _forms[FormIndex] = ui->formIndex;
    _forms[FormPreview] = ui->formPreview;
    _forms[FormSuccess] = ui->formSuccess;

    switchTo(FormIndex);
    selectEpub("E:\\downloads\\moby-dick-20120118.epub");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchTo(const Form f)
{
    foreach( Form key, _forms.keys() )
    {
        QWidget* form = _forms.value(key);
        if(key == f)
        {
            form->setVisible(true);
        }
        else
        {
            form->setVisible(false);
        }
    }

}

void MainWindow::openApkInFolder()
{
    qDebug() << "Open in folder";
}

void MainWindow::newEpub()
{
    qDebug() << "New epub";
}

void MainWindow::tryAgain()
{
    startConversion();
}

void MainWindow::selectEpub(QString epub_file)
{
    EpubInfo info(epub_file);
    if(!info.isValidEpub())
    {
        QMessageBox::critical(this, tr("Error"), tr("This is not a valid EPub file. Please select another file"));
        return;
    }
    this->setWindowTitle(APPLICATION_NAME + " - " + epub_file);

    ui->formPreview->selectEpub(info);
    switchTo(FormPreview);
}


void MainWindow::conversionFinished(bool success, QString error)
{
    if(success)
    {
        ui->formSuccess->setBookName(ui->formPreview->getBookName());
        switchTo(FormSuccess);
    }
    else
    {
        ui->formFailed->setBookName(ui->formPreview->getBookName());
        ui->formFailed->setError(error);
        ui->formFailed->setLog(ui->formCoversion->getLog());
        switchTo(FormFailed);
    }
}

void MainWindow::startConversion()
{
    PreviewWidget* preview = ui->formPreview;
    ConversionWidget* conversion = ui->formCoversion;

    if(preview->hasCover())
    {
        conversion->setImage(preview->getCover());
    }
    else
    {
        conversion->useDefaultImage();
    }

    conversion->setBookName(preview->getBookName());
    conversion->setInputEpub(preview->getEpubFile());
    conversion->setPackageName(preview->getPackageName());
    conversion->setOutputPath(preview->getOutputPath());

    conversion->startConversion();
    switchTo(FormConversion);
}

