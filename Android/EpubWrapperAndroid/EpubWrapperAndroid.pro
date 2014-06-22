#-------------------------------------------------
#
# Project created by QtCreator 2014-06-22T19:38:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EpubWrapperAndroid
TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin/debug/
} else {
    DESTDIR = $$PWD/bin/release/
}


SOURCES += main.cpp\
        MainWindow.cpp \
    Android/AndroidCompile.cpp \
    Utils/FileUtils.cpp

HEADERS  += MainWindow.h \
    Android/AndroidCompile.h \
    Utils/FileUtils.h

FORMS    += MainWindow.ui
