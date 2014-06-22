#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Android/AndroidCompile.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void onLog(QString text);
    void onWarning(QString text);
    void onError(QString text);
    void onFinish(bool success, QString text);
private:
    Ui::MainWindow *ui;
    AndroidCompile _compiler;
};

#endif // MAINWINDOW_H
