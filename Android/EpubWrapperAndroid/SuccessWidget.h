#ifndef SUCCESSWIDGET_H
#define SUCCESSWIDGET_H

#include <QWidget>

namespace Ui {
class SuccessWidget;
}

class SuccessWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SuccessWidget(QWidget *parent = 0);
    ~SuccessWidget();
    
private:
    Ui::SuccessWidget *ui;
};

#endif // SUCCESSWIDGET_H
