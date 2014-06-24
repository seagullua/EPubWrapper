#ifndef CREATEICON_H
#define CREATEICON_H
#include <QString>
#include <QPixmap>
class CreateIcon
{
public:
    static bool createSquareIcon(QString input_file, int size, QString output_file);
    static bool createSquareIcon(QPixmap input_file, int size, QString output_file);
};

#endif // CREATEICON_H
