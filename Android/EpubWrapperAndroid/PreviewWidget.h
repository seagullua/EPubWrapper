#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include "Utils/EpubInfo.h"
namespace Ui {
class PreviewWidget;
}

class PreviewWidget : public QWidget
{
    Q_OBJECT
signals:
    void startConversion();
public:
    explicit PreviewWidget(QWidget *parent = 0);
    ~PreviewWidget();
    void selectEpub(const EpubInfo& info);
    bool hasCover() const;
    QPixmap getCover() const;
    QString getEpubFile() const;
    QString getOutputPath() const;
    QString getBookName() const;
    QString getPackageName() const;
private slots:
    void updatePackageName(QString new_name);
    void selectCover();
    void saveTo();
private:
    void setCover(QPixmap);
    QString _epub_file;
    bool _has_cover;
    QPixmap _cover;

    Ui::PreviewWidget *ui;
};

#endif // PREVIEWWIDGET_H
