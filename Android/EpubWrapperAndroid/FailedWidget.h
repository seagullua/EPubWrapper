#ifndef FAILEDWIDGET_H
#define FAILEDWIDGET_H

#include <QWidget>

namespace Ui {
class FailedWidget;
}

class FailedWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FailedWidget(QWidget *parent = 0);
    ~FailedWidget();
    
private:
    Ui::FailedWidget *ui;
};

#endif // FAILEDWIDGET_H
