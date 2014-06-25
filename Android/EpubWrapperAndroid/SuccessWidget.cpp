#include "SuccessWidget.h"
#include "ui_SuccessWidget.h"

SuccessWidget::SuccessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuccessWidget)
{
    ui->setupUi(this);

    connect(ui->resultNew, SIGNAL(clicked()), this, SIGNAL(newEpub()));
    connect(ui->resultOpenFolder, SIGNAL(clicked()), this, SIGNAL(openFolder()));

}
void SuccessWidget::setBookName(QString v)
{
    ui->resultBookName2->setText(v);
}

SuccessWidget::~SuccessWidget()
{
    delete ui;
}
