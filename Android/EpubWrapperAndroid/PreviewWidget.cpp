#include "PreviewWidget.h"
#include "ui_PreviewWidget.h"

#include <QMessageBox>
#include "Utils/EpubInfo.h"
#include "Utils/Naming.h"

static const QSize COVER_PREVIEW(150, 200);

PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWidget)
{
    ui->setupUi(this);

    connect(ui->convert, SIGNAL(clicked()), this, SIGNAL(startConversion()));

    ui->coverPreview->setMinimumSize(COVER_PREVIEW);

    connect(ui->bookName, SIGNAL(textChanged(QString)), this, SLOT(updatePackageName(QString)));

}

bool PreviewWidget::hasCover() const
{
    return _has_cover;
}
QPixmap PreviewWidget::getCover() const
{
    return _cover;
}
QString PreviewWidget::getEpubFile() const
{
    return _epub_file;
}
QString PreviewWidget::getOutputPath() const
{
    return ui->saveToPath->text();
}
QString PreviewWidget::getBookName() const
{
    return ui->bookName->text();
}
QString PreviewWidget::getPackageName() const
{
    return ui->androidPackage->text();
}

void PreviewWidget::selectEpub(const EpubInfo& info)
{
    _epub_file = info.getFileName();

    _has_cover = false;
    if(info.hasCover())
    {
        ui->bookName->setText(info.getBookName());
        _has_cover = true;
        _cover = info.getCover();
        QPixmap thumb = _cover.scaled(COVER_PREVIEW, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        //qDebug() << ui->coverPreview->size();
        ui->coverPreview->setPixmap(thumb);
        ui->coverImageFile->setText(tr("(default)"));
    }
    else
    {
        ui->coverImageFile->setText(tr("(no cover)"));
    }
    ui->saveToPath->setText(_epub_file+".apk");
}

void PreviewWidget::updatePackageName(QString new_name)
{
    QString book_name = new_name;
    QString latin = Naming::createLatinName(book_name);
    QString package_name = "book." + Naming::forPackageName(latin);
    ui->androidPackage->setText(package_name);
}

PreviewWidget::~PreviewWidget()
{
    delete ui;
}
