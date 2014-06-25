#include "IndexWidget.h"
#include "ui_IndexWidget.h"

IndexWidget::IndexWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndexWidget)
{
    ui->setupUi(this);
}

IndexWidget::~IndexWidget()
{
    delete ui;
}
