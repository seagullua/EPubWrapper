#-------------------------------------------------
#
# Project created by QtCreator 2014-06-22T19:38:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EpubWrapperAndroid
TEMPLATE = app

RC_FILE = res.rc



CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin/debug/
} else {
    DESTDIR = $$PWD/bin/release/
}
INCLUDEPATH += $$PWD/../../libraries/zlib
INCLUDEPATH += $$PWD/../../libraries/QuaZIP
DEFINES += QUAZIP_STATIC

SOURCES += main.cpp\
        MainWindow.cpp \
    Android/AndroidCompile.cpp \
    Utils/FileUtils.cpp \
    Utils/CreateIcon.cpp \
    Utils/EpubInfo.cpp \
    ../../libraries/QuaZIP/quazip/quazipnewinfo.cpp \
    ../../libraries/QuaZIP/quazip/quazipfile.cpp \
    ../../libraries/QuaZIP/quazip/quazipdir.cpp \
    ../../libraries/QuaZIP/quazip/quazip.cpp \
    ../../libraries/QuaZIP/quazip/quaziodevice.cpp \
    ../../libraries/QuaZIP/quazip/quagzipfile.cpp \
    ../../libraries/QuaZIP/quazip/quacrc32.cpp \
    ../../libraries/QuaZIP/quazip/quaadler32.cpp \
    ../../libraries/QuaZIP/quazip/qioapi.cpp \
    ../../libraries/QuaZIP/quazip/JlCompress.cpp \
    ../../libraries/QuaZIP/quazip/zip.c \
    ../../libraries/QuaZIP/quazip/unzip.c \
    ../../libraries/zlib/zutil.c \
    ../../libraries/zlib/uncompr.c \
    ../../libraries/zlib/trees.c \
    ../../libraries/zlib/inftrees.c \
    ../../libraries/zlib/inflate.c \
    ../../libraries/zlib/inffast.c \
    ../../libraries/zlib/infback.c \
    ../../libraries/zlib/gzwrite.c \
    ../../libraries/zlib/gzread.c \
    ../../libraries/zlib/gzlib.c \
    ../../libraries/zlib/gzclose.c \
    ../../libraries/zlib/deflate.c \
    ../../libraries/zlib/crc32.c \
    ../../libraries/zlib/compress.c \
    ../../libraries/zlib/adler32.c \
    Utils/Naming.cpp \
    IndexWidget.cpp \
    PreviewWidget.cpp \
    SuccessWidget.cpp \
    FailedWidget.cpp \
    ConversionWidget.cpp

HEADERS  += MainWindow.h \
    Android/AndroidCompile.h \
    Utils/FileUtils.h \
    Utils/CreateIcon.h \
    Utils/EpubInfo.h \
    ../../libraries/QuaZIP/quazip/zip.h \
    ../../libraries/QuaZIP/quazip/unzip.h \
    ../../libraries/QuaZIP/quazip/quazipnewinfo.h \
    ../../libraries/QuaZIP/quazip/quazipfileinfo.h \
    ../../libraries/QuaZIP/quazip/quazipfile.h \
    ../../libraries/QuaZIP/quazip/quazipdir.h \
    ../../libraries/QuaZIP/quazip/quazip_global.h \
    ../../libraries/QuaZIP/quazip/quazip.h \
    ../../libraries/QuaZIP/quazip/quaziodevice.h \
    ../../libraries/QuaZIP/quazip/quagzipfile.h \
    ../../libraries/QuaZIP/quazip/quacrc32.h \
    ../../libraries/QuaZIP/quazip/quachecksum32.h \
    ../../libraries/QuaZIP/quazip/quaadler32.h \
    ../../libraries/QuaZIP/quazip/JlCompress.h \
    ../../libraries/QuaZIP/quazip/ioapi.h \
    ../../libraries/QuaZIP/quazip/crypt.h \
    ../../libraries/zlib/zutil.h \
    ../../libraries/zlib/zlib.h \
    ../../libraries/zlib/zconf.h \
    ../../libraries/zlib/trees.h \
    ../../libraries/zlib/inftrees.h \
    ../../libraries/zlib/inflate.h \
    ../../libraries/zlib/inffixed.h \
    ../../libraries/zlib/inffast.h \
    ../../libraries/zlib/gzguts.h \
    ../../libraries/zlib/deflate.h \
    ../../libraries/zlib/crc32.h \
    Utils/Naming.h \
    IndexWidget.h \
    PreviewWidget.h \
    SuccessWidget.h \
    FailedWidget.h \
    ConversionWidget.h

FORMS    += MainWindow.ui \
    IndexWidget.ui \
    PreviewWidget.ui \
    SuccessWidget.ui \
    FailedWidget.ui \
    ConversionWidget.ui
