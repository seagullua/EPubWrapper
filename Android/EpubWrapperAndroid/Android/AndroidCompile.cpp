#include "AndroidCompile.h"
#include <QDir>
#include <QDateTime>
#include "Utils/FileUtils.h"
#include "Utils/CreateIcon.h"
#include <QCoreApplication>

AndroidCompile::AndroidCompile()
    : _default_cover(true)
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


void AndroidCompile::setCoverImage(QPixmap img)
{
    _cover_image = img;
    _default_cover = false;
}

void AndroidCompile::setJdkPath(QString path)
{
    _jdk_path = path;
}

void AndroidCompile::prepareEnvironment()
{
    _environment = QProcessEnvironment();
    QString PATH = _jdk_path+";"+_android_sdk_path+";"+_ant_path;
    _environment.insert("PATH", PATH);
    _environment.insert("JAVA_HOME", _jdk_path);
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
    emit logMessage(tr("Template path: %1").arg(_template_path));
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

void AndroidCompile::createCoverImage(
        QString icon_folder, int icon_size)
{
    QString icon_name = "fbreader.png";
    QString output_name = QDir(_build_dir).absoluteFilePath(
                QDir::toNativeSeparators("res/"+icon_folder+"/"+icon_name));

    if(!CreateIcon::createSquareIcon(_cover_image, icon_size, output_name))
    {
        throw tr("Can't create cover image: %1").arg(icon_folder);
    }
    else
    {
        emit logMessage(tr("Cover image created: %1").arg(icon_folder));
    }

}

void AndroidCompile::createProjectCoverImages()
{
    if(!_default_cover)
    {
        createCoverImage("drawable-hdpi", 72);
        createCoverImage("drawable-ldpi", 36);
        createCoverImage("drawable-mdpi", 48);
        createCoverImage("drawable-xhdpi", 96);
        createCoverImage("drawable-xxhdpi", 144);
    }
}

void AndroidCompile::copyEpub()
{
    QString book_epub = QDir(_build_dir).absoluteFilePath(QDir::toNativeSeparators("assets/data/book.epub"));

    if(QFile::copy(_input_epub_name, book_epub))
    {
        emit logMessage(tr("Copy book: %1").arg(_input_epub_name));
    }
    else
    {
        throw tr("Can't copy book: %1").arg(_input_epub_name);
    }
}

void AndroidCompile::buildApk()
{
    emit logMessage(tr("Compiling Android Project..."));
    QProcess process;
    QStringList arguments;
    arguments.push_back("/C");
    arguments.push_back("ant.bat");
    arguments.push_back("release");
    process.setProcessEnvironment(_environment);
    process.setWorkingDirectory(_build_dir);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("cmd.exe", arguments);

    // Wait for it to start
    if(!process.waitForStarted())
    {
        throw tr("Can't start Ant");
    }

    while(process.waitForReadyRead())
    {
        QByteArray data = process.readAll();
        emit logMessage(data.data());
        QCoreApplication::processEvents();
    }

    process.waitForFinished();

    if(process.exitCode() != 0)
    {
        throw tr("Build Android Project failed");
    }
}
void AndroidCompile::copyFinalApk()
{
    QString apk = QDir(_build_dir).absoluteFilePath(QDir::toNativeSeparators("bin/Wrapper-release.apk"));
    if(!QFile::exists(apk))
    {
        throw tr("Build file not found: %1").arg(apk);
    }

    if(QFile::exists(_output_apk_name))
    {
        warningMessage(tr("Output file exists: %1").arg(_output_apk_name));
        if(QFile(_output_apk_name).remove())
        {
            logMessage(tr("Remove old output file"));
        }
        else
        {
            throw tr("Can't remove output file: %1").arg(_output_apk_name);
        }
    }

    //TODO: mkdir
    if(QFile::copy(apk, _output_apk_name))
    {
        logMessage(tr("Apk moved"));
    }
    else
    {
        throw tr("Can't write output file: %1").arg(_output_apk_name);
    }
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

    {
        //Update local.properties
        QString prop_file = QDir(_build_dir).absoluteFilePath("local.properties");

        emit logMessage(tr("Create: %1").arg(prop_file));
        FileUtils::writeFileContents(prop_file, QString("sdk.dir=%1").arg(QDir::fromNativeSeparators(_android_sdk_path)));
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
        copyEpub();
        buildApk();
        copyFinalApk();
    }
    catch (QString error)
    {
        result_text = error;
        success = false;
    }

    cleanOutputDir();

    emit finished(success, result_text);
}


