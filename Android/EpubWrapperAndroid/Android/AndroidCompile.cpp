#include "AndroidCompile.h"
#include <QDir>
#include <QDateTime>
#include "Utils/FileUtils.h"

AndroidCompile::AndroidCompile()
{

}


void AndroidCompile::setTemplatePath(QString path)
{
    _template_path = path;
}

void AndroidCompile::setAndroidSdkPath(QString path)
{
    _android_sdk_path = path;
}

void AndroidCompile::setOutputApkName(QString path)
{
    _output_apk_name = path;
}


void AndroidCompile::setAntPath(QString path)
{
    _ant_path = path;
}


void AndroidCompile::setPackageName(QString name)
{
    _package_name = name;
}


void AndroidCompile::setBookName(QString name)
{
    _book_name = name;
}


void AndroidCompile::setInputEpub(QString path)
{
    _input_epub_name = path;
}


void AndroidCompile::setCoverImageName(QString path)
{
    _cover_image_name = path;
}

void AndroidCompile::setJdkPath(QString path)
{
    _jdk_path = path;
}

void AndroidCompile::prepareEnvironment()
{
    _environment = QProcessEnvironment::systemEnvironment();
    QString PATH = _jdk_path+";"+_android_sdk_path+";"+_ant_path;
    _environment.insert("PATH", PATH);
    emit logMessage(tr("PATH: %1").arg(PATH));
}

void AndroidCompile::prepareOutputDir()
{
    QDir temp(QDir::tempPath());
    QString time = QString::number(QDateTime::currentDateTime().toTime_t());
    _build_dir = temp.absoluteFilePath(_package_name+time);

    QDir dir(_build_dir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    emit logMessage(tr("Build dir: %1").arg(_build_dir));
}

void AndroidCompile::cleanOutputDir()
{
    if(FileUtils::removeDir(_build_dir))
    {
        emit logMessage(tr("Clean dir: %1").arg(_build_dir));
    }
    else
    {
        emit warningMessage(tr("Can't clean dir: %1").arg(_build_dir));
    }
}

void AndroidCompile::startCompilation()
{
    bool success = true;
    QString result_text = "";

    try
    {
        prepareEnvironment();
        prepareOutputDir();
    }
    catch (QString error)
    {
        result_text = error;
        success = false;
    }

    cleanOutputDir();

    emit finished(success, result_text);
}
