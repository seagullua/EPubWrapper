#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    enum Form
    {
        FormIndex,
        FormPreview,
        FormConversion,
        FormSuccess,
        FormFailed
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void startConversion();
    void conversionFinished(bool success, QString error);
    void openApkInFolder();
    void newEpub();
    void tryAgain();
    void openEpub();
private:
    void switchTo(const Form);
    void selectEpub(QString epub_file);


    void openInExplorer(QString file);
    typedef QMap<Form, QWidget*> FormsMap;

    FormsMap _forms;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
