#include "SuccessWidget.h"
#include "ui_SuccessWidget.h"

SuccessWidget::SuccessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuccessWidget)
{
    ui->setupUi(this);
}

SuccessWidget::~SuccessWidget()
{
    delete ui;
}
