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
private:
    QString _file_name;
    QByteArray _cover;
    QString _cover_type;
    QString _book_title;
};

#endif // EPUBINFO_H
