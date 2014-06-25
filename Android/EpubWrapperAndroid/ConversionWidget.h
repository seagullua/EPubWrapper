#ifndef CONVERSIONWIDGET_H
#define CONVERSIONWIDGET_H

#include <QWidget>

#include <QSharedPointer>
#include "Android/AndroidCompile.h"
typedef QSharedPointer<AndroidCompile> AndroidCompilePtr;

namespace Ui {
class ConversionWidget;
}

class ConversionWidget : public QWidget
{
    Q_OBJECT
signals:
    void finished(bool success, QString text);
public:
    explicit ConversionWidget(QWidget *parent = 0);
    ~ConversionWidget();

    void setBookName(QString book_name);
    void setPackageName(QString package_name);
    void setImage(QPixmap image);
    void setInputEpub(QString epub);
    void setOutputPath(QString output);
    void useDefaultImage();
    void startConversion();
    QString getLog() const;
private slots:
    void onLog(QString text);
    void onWarning(QString text);
    void onError(QString text);
    void onFinish(bool success, QString text);

    void onProgress(int steps_made, int steps);
    void showLog();
private:
    QString _epub_file;
    QString _book_name;
    QString _package_name;
    QString _output_path;
    QPixmap _cover;
    bool _has_cover;


    QString getProjectDir(QString path);
    Ui::ConversionWidget *ui;

    AndroidCompilePtr _compiler;
};

#endif // CONVERSIONWIDGET_H
