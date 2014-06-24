#include "EpubInfo.h"
#include <quazip/JlCompress.h>
#include <QDebug>
#include <QXmlStreamReader>

QString getPackagePath(const QByteArray& container_xml)
{
    QXmlStreamReader xml(container_xml);
    while(!xml.atEnd() &&  !xml.hasError()) {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xml.readNext();
        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement)
        {
            /* If it's named persons, we'll go to the next.*/
            if(xml.name() == "rootfile")
            {
                return xml.attributes().value("full-path").toString();
            }
        }
    }
    return "";
}

QString getBookTitle(const QByteArray& package_file)
{
    QXmlStreamReader xml(package_file);
    while(!xml.atEnd() &&  !xml.hasError()) {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xml.readNext();
        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement)
        {
            /* If it's named persons, we'll go to the next.*/
            //qDebug() << xml.name() << xml.text();
            if(xml.name() == "title")
            {
                xml.readNext();
                return xml.text().toString();
            }
        }
    }
    return "";
}

QString getFirstImage(const QByteArray& package_file, QString& img_type)
{
    QXmlStreamReader xml(package_file);
    while(!xml.atEnd() &&  !xml.hasError()) {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xml.readNext();
        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement)
        {
            /* If it's named persons, we'll go to the next.*/
            //qDebug() << xml.name() << xml.text();
            if(xml.name() == "item")
            {
                QXmlStreamAttributes attr = xml.attributes();
                QString media_type = attr.value("media-type").toString();
                QString IMAGE = "image";
                if(media_type.size() >= IMAGE.size())
                {
                    if(media_type.mid(0, IMAGE.size())==IMAGE)
                    {
                        img_type = media_type.mid(IMAGE.size() + 1);
                        return attr.value("href").toString();
                    }
                }
            }
        }
    }
    return "";
}

QByteArray getFileContent(QuaZip& zip, QString file_name)
{
    QByteArray res;

    const int BUFFER_SIZE = 10000000;
    res.resize(BUFFER_SIZE);

    for(bool f=zip.goToFirstFile(); f; f=zip.goToNextFile())
    {
        //qDebug() << zip.getCurrentFileName();
        if(zip.getCurrentFileName() == file_name)
        {
            QuaZipFile file(&zip);
            file.open(QIODevice::ReadOnly);
            int readed = file.read(res.begin(),BUFFER_SIZE);
            res.resize(readed);
            file.close();
            break;
            return res;
        }

    }
    res.resize(0);
    return res;
}

QString EpubInfo::getBookName() const
{
    return _book_title;
}
bool EpubInfo::hasCover() const
{
    return _cover.size() > 0;
}
QPixmap EpubInfo::getCover() const
{
    return QPixmap(_cover, _cover_type.toStdString().c_str());
}


EpubInfo::EpubInfo(QString file_name)
{
    QuaZip zip(file_name);
    zip.open(QuaZip::mdUnzip);

    QString package_file = getPackagePath(getFileContent(zip, "META-INF/container.xml"));
    QByteArray package = getFileContent(zip, package_file);
    _book_title = getBookTitle(package);

    //TODO: apply path for cover
    QString cover_name = getFirstImage(package, _cover_type);

    if(cover_name.size() > 0)
    {
        qDebug() << cover_name;
        _cover = getFileContent(zip, cover_name);
        qDebug() << _cover.size();

    }
}
