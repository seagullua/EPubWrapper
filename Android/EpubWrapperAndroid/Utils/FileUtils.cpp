#include "FileUtils.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>
#include <QCoreApplication>

bool FileUtils::removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    QCoreApplication::processEvents();
    return result;
}

bool FileUtils::copyDir(const QString &srcPath, const QString &dstPath)
{
    if(!QDir(dstPath).exists())
    {
        QDir parentDstDir(QFileInfo(dstPath).path());
        if (!parentDstDir.mkdir(QFileInfo(dstPath).fileName()))
            return false;
    }


    QDir srcDir(srcPath);
    foreach(const QFileInfo &info, srcDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
        QString srcItemPath = QDir(srcPath).absoluteFilePath(info.fileName());
        QString dstItemPath = QDir(dstPath).absoluteFilePath(info.fileName());
        if (info.isDir()) {
            if (!copyDir(srcItemPath, dstItemPath)) {
                return false;
            }
        } else if (info.isFile()) {
            if (!QFile::copy(srcItemPath, dstItemPath)) {
                return false;
            }
        } else {
            qDebug() << "Unhandled item" << info.filePath() << "in cpDir";
        }
    }
    QCoreApplication::processEvents();
    return true;
}

QString FileUtils::readFileContents(const QString& file_name)
{
    QFile f(file_name);
    if (!f.open(QFile::ReadOnly | QFile::Text))
    {
        throw QObject::tr("Can't open file: %1").arg(file_name);
    }
    QTextStream in(&f);
    in.setCodec("UTF-8");
    return in.readAll();
}

void FileUtils::writeFileContents(const QString& file_name, const QString& contents)
{
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw QObject::tr("Can't save file: %1").arg(file_name);
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << contents;
}

