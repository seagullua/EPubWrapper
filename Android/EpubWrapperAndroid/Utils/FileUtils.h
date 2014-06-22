#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
class FileUtils
{
public:
    /**
     * @brief Deletes dir with all content
     * @param dirName
     * @return
     */
    static bool removeDir(const QString &dirName);

    static bool copyDir(const QString &srcPath, const QString &dstPath);

    static QString readFileContents(const QString& file_name);
    static void writeFileContents(const QString& file_name, const QString& contents);
};

#endif // FILEUTILS_H
