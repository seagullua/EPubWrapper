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

void AndroidCompile::copyProjectTemplate()
{
    emit logMessage(tr("Copying project template..."));
    if(FileUtils::copyDir(_template_path, _build_dir))
    {
        emit logMessage(tr("Project template ready"));
    }
    else
    {
        throw QString("Copy project template failed");
    }
}

void AndroidCompile::createProjectCoverImages()
{
    //TODO: implement
}

void AndroidCompile::applyPackageAndBookName()
{
    {
        //Update manifest file
        QString manifest_file = QDir(_build_dir).absoluteFilePath("AndroidManifest.xml");

        emit logMessage(tr("Update: %1").arg(manifest_file));
        QString manifest = FileUtils::readFileContents(manifest_file);
        manifest = manifest.replace("{{bookName}}", _book_name);
        manifest = manifest.replace("com.book.test", _package_name);
        FileUtils::writeFileContents(manifest_file, manifest);
    }

    {
        //Update R file
        QString R_file = QDir(_build_dir).absoluteFilePath(QDir::toNativeSeparators("src/org/geometerplus/zlibrary/ui/android/R.java"));
        emit logMessage(tr("Update: %1").arg(R_file));

        QString R = FileUtils::readFileContents(R_file);
        R = R.replace("com.book.test", _package_name);
        FileUtils::writeFileContents(R_file, R);
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
        copyProjectTemplate();
        createProjectCoverImages();
        applyPackageAndBookName();
    }
    catch (QString error)
    {
        result_text = error;
        success = false;
    }

    //cleanOutputDir();

    emit finished(success, result_text);
}


