#include "PreviewWidget.h"
#include "ui_PreviewWidget.h"

#include <QMessageBox>
#include "Utils/EpubInfo.h"
#include "Utils/Naming.h"
#include <QFileDialog>

static const QSize COVER_PREVIEW(150, 200);

PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewWidget)
{
    ui->setupUi(this);

    connect(ui->convert, SIGNAL(clicked()), this, SIGNAL(startConversion()));

    ui->coverPreview->setMinimumSize(COVER_PREVIEW);

    connect(ui->bookName, SIGNAL(textChanged(QString)), this, SLOT(updatePackageName(QString)));
    connect(ui->selectCoverImage, SIGNAL(clicked()), this, SLOT(selectCover()));
    connect(ui->selectSaveTo, SIGNAL(clicked()), this, SLOT(saveTo()));
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

void PreviewWidget::setCover(QPixmap p)
{
    _has_cover = true;
    _cover = p;
    QPixmap thumb = _cover.scaled(
                COVER_PREVIEW, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->coverPreview->setPixmap(thumb);
}

void PreviewWidget::selectEpub(const EpubInfo& info)
{
    _epub_file = info.getFileName();

    ui->saveToPath->setText(_epub_file+".apk");
    _has_cover = false;

    QString book_name = info.getBookName();
    if(book_name.size()==0)
    {
        book_name = tr("Noname");
    }
    ui->bookName->setText(book_name);

    if(info.hasCover())
    {
        setCover(info.getCover());
        ui->coverImageFile->setText(tr("(default)"));
    }
    else
    {
        ui->coverImageFile->setText(tr("(no cover)"));
    }


}

void PreviewWidget::updatePackageName(QString new_name)
{
    QString book_name = new_name;
    QString latin = Naming::createLatinName(book_name);
    QString save_name = Naming::forPackageName(latin);
    QString package_name = "book." + save_name;
    ui->androidPackage->setText(package_name);

    QString full_path = ui->saveToPath->text();
    QString output_dir = full_path.mid(0, full_path.size() -
                                             QDir(full_path).dirName().size());


    ui->saveToPath->setText(output_dir + save_name + ".apk");
}

void PreviewWidget::selectCover()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Choose Cover"),
                                                     _epub_file,
                                                     tr("Images (*.png *.jpg *.jpeg)"));

    QPixmap img;
    if(img.load(file_name))
    {
        setCover(img);
        ui->coverImageFile->setText(file_name);

    }

}

void PreviewWidget::saveTo()
{
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save APK"),
                                                     ui->saveToPath->text(),
                                                     tr("Android APK (*.apk)"));
    if(file_name.size() > 0)
    {
        ui->saveToPath->setText(file_name);
    }
}

PreviewWidget::~PreviewWidget()
{
    delete ui;
}
