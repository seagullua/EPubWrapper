#include "FailedWidget.h"
#include "ui_FailedWidget.h"
#include <QScrollBar>
FailedWidget::FailedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FailedWidget)
{
    ui->setupUi(this);
    connect(ui->resultTryAgain, SIGNAL(clicked()), this, SIGNAL(tryAgain()));
    connect(ui->resultShowLog, SIGNAL(clicked()), this, SLOT(showLog()));

    ui->resultLog->setVisible(false);
}
void FailedWidget::showLog()
{
    ui->resultLog->setVisible(true);
    ui->resultLog->verticalScrollBar()->setValue(ui->resultLog->verticalScrollBar()->maximum());
    ui->resultLog->horizontalScrollBar()->setValue(ui->resultLog->horizontalScrollBar()->minimum());
    ui->resultShowLog->setVisible(false);
}

void FailedWidget::setBookName(QString v)
{
    ui->resultBookName->setText(v);
}

void FailedWidget::setError(QString v)
{
    ui->resultErrorMessage->setText(v);
}

void FailedWidget::setLog(QString v)
{
    ui->resultLog->setText(v);
}

FailedWidget::~FailedWidget()
{
    delete ui;
}
