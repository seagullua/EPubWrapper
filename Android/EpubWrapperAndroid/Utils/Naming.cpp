#include "Naming.h"
#include <QString>
#include <QMap>
#include <QSet>

QMap<QString, QString> getReplacements()
{
    QMap<QString, QString> toTranslit;
    toTranslit[QChar(1072)] = 'a';
    toTranslit[QChar(1073)] = 'b';
    toTranslit[QChar(1074)] = 'v';
    toTranslit[QChar(1075)] = 'g';
    toTranslit[QChar(1076)] = 'd';
    toTranslit[QChar(1077)] = 'e';
    toTranslit[QChar(1078)] = "zh";
    toTranslit[QChar(1079)] = 'z';
    toTranslit[QChar(1080)] = 'i';
    toTranslit[QChar(1081)] = 'y';
    toTranslit[QChar(1082)] = 'k';
    toTranslit[QChar(1083)] = 'l';
    toTranslit[QChar(1084)] = 'm';
    toTranslit[QChar(1085)] = 'n';
    toTranslit[QChar(1086)] = 'o';
    toTranslit[QChar(1087)] = 'p';
    toTranslit[QChar(1088)] = 'r';
    toTranslit[QChar(1089)] = 's';
    toTranslit[QChar(1090)] = 't';
    toTranslit[QChar(1091)] = 'u';
    toTranslit[QChar(1092)] = 'f';
    toTranslit[QChar(1093)] = 'h';
    toTranslit[QChar(1094)] = 'c';
    toTranslit[QChar(1095)] = "ch";
    toTranslit[QChar(1096)] = "sh";
    toTranslit[QChar(1097)] = "shch";
    toTranslit[QChar(1098)] = "";
    toTranslit[QChar(1099)] = 'y';
    toTranslit[QChar(1100)] = "";
    toTranslit[QChar(1101)] = "e";
    toTranslit[QChar(1102)] = "iu";
    toTranslit[QChar(1103)] = "ia";
    toTranslit[QChar(1105)] = "io";
    toTranslit[QChar(1108)] = "ie";
    toTranslit[QChar(1110)] = 'i';
    toTranslit[QChar(1111)] = "i";
    toTranslit["-"] = "_";
    toTranslit[" "] = "_";

    return toTranslit;
}


QSet<QChar> getValidForPackage()
{
    QSet<QChar> res;
    const QString VALID_FOR_PACKAGE = "qwertyuiopasdfghjklzxcvbnm_0123456789";

    for (int i = 0; i < VALID_FOR_PACKAGE.length(); ++i)
    {
        res.insert(VALID_FOR_PACKAGE[i]);
    }

    return res;
}

QString Naming::forPackageName(const QString& name)
{
    static QSet<QChar> valid = getValidForPackage();
    QString res;
    for (int i = 0; i < name.length(); ++i)
    {
        QChar ch = name[i];
        ch = ch.toLower();
        if(valid.find(ch) != valid.end())
        {
            res += ch;
        }
    }

    if(res.size() == 0)
        res = "undefined";

    if(res[0] == '_' || res[0].isDigit())
    {
        res = "x" + res;
    }
    return res;
}

QString Naming::createLatinName(const QString &name)
{
    static QMap<QString, QString> toTranslit = getReplacements();
    QString res;

    for (int i = 0; i < name.length(); ++i) {
        const QString ch = name.at(i);
        const QString lowerCh = ch.toLower();
        if (toTranslit.contains(lowerCh)) {
            QString tmp = ch == lowerCh ? toTranslit[lowerCh] : toTranslit[lowerCh].toUpper();
            res += tmp;
        } else
            res += ch;
    }

    return res;
}
