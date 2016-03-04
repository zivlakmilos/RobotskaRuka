#-------------------------------------------------
#
# Project created by QtCreator 2016-02-24T00:48:17
#
#-------------------------------------------------

QT       += core gui
CONFIG   += extserialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobotskaRuka
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           opencvwidget.cpp \
           centralwidget.cpp

HEADERS  += mainwindow.h \
            opencvwidget.h \
            centralwidget.h

FORMS    += mainwindow.ui \
            centralwidget.ui

LIBS     += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core

release:DESTDIR = release
release:OBJECTS_DIR = release/.obj
release:MOC_DIR = release/.moc
release:RCC_DIR = release/.rcc
release:UI_DIR = release/.ui

debug:DESTDIR = debug
debug:OBJECTS_DIR = debug/.obj
debug:MOC_DIR = debug/.moc
debug:RCC_DIR = debug/.rcc
debug:UI_DIR = debug/.ui
