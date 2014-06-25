#ifndef EPUBINFO_H
#define EPUBINFO_H
#include <QString>
#include <QPixmap>
class EpubInfo
{
public:
    EpubInfo(QString file_name);
    QString getBookName() const;
    bool hasCover() const;
    QPixmap getCover() const;
    QString getFileName() const;
    bool isValidEpub() const;
private:
    QString _file_name;
    bool _has_cover;
    bool _is_valid_epub;
    QString _cover_type;
    QString _book_title;
    QPixmap _cover_image;
};

#endif // EPUBINFO_H
