#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class PreviewWidget;
}

class PreviewWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PreviewWidget(QWidget *parent = 0);
    ~PreviewWidget();
    void selectEpub(QString epub_file);
private:
    void updatePackageName(QString new_name);
    QString _epub_file;
    bool _has_cover;
    QPixmap _cover;

    Ui::PreviewWidget *ui;
};

#endif // PREVIEWWIDGET_H
