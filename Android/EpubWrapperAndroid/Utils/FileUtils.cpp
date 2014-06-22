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
