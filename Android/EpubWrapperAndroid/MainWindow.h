#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QThread>
#include <QSharedPointer>
#include "Android/AndroidCompile.h"

//typedef QSharedPointer<QThread> QThreadPtr;
typedef QSharedPointer<AndroidCompile> AndroidCompilePtr;


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
    void onStart();
    void onProgress(int steps_made, int steps);
    void updatePackageName(QString new_name);
    void cancelRunningTask();
private:
    void selectEpub(QString epub_file);

    //QThreadPtr _thread;
    QString getProjectDir(QString path);
    QString _epub_file;
    QPixmap _cover;
    bool _has_cover;
    Ui::MainWindow *ui;
    AndroidCompilePtr _compiler;
};

#endif // MAINWINDOW_H
