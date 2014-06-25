#ifndef CREATEICON_H
#define CREATEICON_H
#include <QString>
#include <QImage>
class CreateIcon
{
public:
    static bool createSquareIcon(QImage input_file, int size, QString output_file);
};

#endif // CREATEICON_H
