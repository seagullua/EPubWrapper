#include "CreateIcon.h"
#include <QPixmap>
#include <QPainter>
#include <QFile>
bool CreateIcon::createSquareIcon(
        QPixmap input_file,
        int size,
        QString output_file)
{
    QPixmap source_scaled = input_file.scaled(
                size,
                size,
                Qt::KeepAspectRatio, Qt::SmoothTransformation);
    int width = source_scaled.width();
    int height = source_scaled.height();

    QPixmap icon(size, size);
    icon.fill(Qt::transparent);

    QPainter p(&icon);
    p.drawPixmap((size-width)/2,
                 (size-height)/2,
                 width,
                 height,
                 source_scaled);
    return icon.save(output_file, "PNG");
}

bool CreateIcon::createSquareIcon(
        QString input_file,
        int size,
        QString output_file)
{
    return createSquareIcon(QPixmap(input_file), size, output_file);
}


