#ifndef NAMING_H
#define NAMING_H
#include <QString>

class Naming
{
public:
    static QString forPackageName(const QString& name);
    static QString createLatinName(const QString &name);
};

#endif // NAMING_H
