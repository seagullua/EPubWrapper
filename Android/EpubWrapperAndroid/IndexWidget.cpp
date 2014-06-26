#include "IndexWidget.h"
#include "ui_IndexWidget.h"

IndexWidget::IndexWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndexWidget)
{
    ui->setupUi(this);
    connect(ui->indexSelectFile, SIGNAL(clicked()), this, SIGNAL(openEpub()));
}

IndexWidget::~IndexWidget()
{
    delete ui;
}
