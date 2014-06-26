#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include "Utils/EpubInfo.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QSettings>

static const QString APPLICATION_NAME(QObject::tr("ePUB to APK"));

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
    connect(ui->formIndex, SIGNAL(openEpub()), this, SLOT(openEpub()));
    _forms[FormConversion] = ui->formCoversion;
    _forms[FormFailed] = ui->formFailed;
    _forms[FormIndex] = ui->formIndex;
    _forms[FormPreview] = ui->formPreview;
    _forms[FormSuccess] = ui->formSuccess;

    switchTo(FormIndex);

    this->setWindowTitle(APPLICATION_NAME);

    //Read file to open from command line
    QStringList arguments = QCoreApplication::arguments();
    if(arguments.size() >= 2)
    {
        QString file_name = arguments.at(1);

        selectEpub(file_name);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openEpub()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Choose ePUB"),
                                                     "",
                                                     tr("ePUB (*.epub)"));
    if(file_name.size() > 0)
    {
        selectEpub(file_name);
    }

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
    openInExplorer(ui->formPreview->getOutputPath());
}

void MainWindow::newEpub()
{
    QString current_exe = QCoreApplication::applicationFilePath();
    QProcess process;
    bool is_ok = process.startDetached(QString("\"%1\"").arg(current_exe));
    qDebug() << "Run new: " << is_ok;
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
        QMessageBox::critical(this, tr("Error"), tr("'%1' is not a valid ePUB file. Please select another file").arg(epub_file));
        return;
    }
    this->setWindowTitle(APPLICATION_NAME + " - " + epub_file);

    ui->formPreview->selectEpub(info);
    switchTo(FormPreview);
}

void MainWindow::openInExplorer(QString file)
{
    QString param;
    if (!QFileInfo(file).isDir())
        param = QLatin1String("/select,");
    param += QDir::toNativeSeparators(file);
    QProcess::startDetached("explorer.exe", QStringList(param));
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

void MainWindow::registerQuickAction()
{
    QString exe_name = QCoreApplication::applicationFilePath();
    exe_name = exe_name.replace("/", "\\");
    QString fileExtension = ".epub";
    QString action_name = "ePUB to APK";


    QSettings settings(QString("HKEY_CURRENT_USER\\SOFTWARE\\Classes"),
                           QSettings::NativeFormat);

    QString documentID = settings.value(QString("%1/Default").arg(fileExtension)).toString();

    if(documentID.size() == 0)
    {
        documentID = "Epub.File";
        settings.setValue(QString("%1/Default").arg(fileExtension), documentID);

    }
    qDebug() << documentID;

    QString DEFAULT_KEY = QString("%1/shell/%2/Default").arg(documentID, action_name);
    settings.setValue(DEFAULT_KEY, action_name);

    settings.setValue(QString("%1/shell/%2/Icon").arg(documentID, action_name),
                      QString("\"%1\",%2").arg(exe_name).arg(0));
    settings.setValue(QString("%1/shell/%2/command/Default").arg(documentID, action_name),
                      "\"" + exe_name + "\" \"%1\"");
}

