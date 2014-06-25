#include "FailedWidget.h"
#include "ui_FailedWidget.h"

FailedWidget::FailedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FailedWidget)
{
    ui->setupUi(this);
}

FailedWidget::~FailedWidget()
{
    delete ui;
}
