#ifndef FAILEDWIDGET_H
#define FAILEDWIDGET_H

#include <QWidget>

namespace Ui {
class FailedWidget;
}

class FailedWidget : public QWidget
{
    Q_OBJECT
signals:
    void tryAgain();
public:
    explicit FailedWidget(QWidget *parent = 0);
    ~FailedWidget();
    void setBookName(QString);
    void setError(QString);
    void setLog(QString);
private slots:
    void showLog();
private:
    Ui::FailedWidget *ui;
};

#endif // FAILEDWIDGET_H
