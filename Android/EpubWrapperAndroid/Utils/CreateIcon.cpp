#include "CreateIcon.h"
#include <QPixmap>
#include <QPainter>
#include <QFile>
bool CreateIcon::createSquareIcon(
        QImage input_file,
        int size,
        QString output_file)
{
    QImage source_scaled = input_file.scaled(
                size,
                size,
                Qt::KeepAspectRatio, Qt::SmoothTransformation);
    int width = source_scaled.width();
    int height = source_scaled.height();

    QImage icon(size, size, QImage::Format_ARGB32);
    icon.fill(Qt::transparent);

    QPainter p(&icon);
    p.drawImage(QRect((size-width)/2,
                      (size-height)/2,
                      width,
                      height),
                source_scaled);
    return icon.save(output_file, "PNG");
}

