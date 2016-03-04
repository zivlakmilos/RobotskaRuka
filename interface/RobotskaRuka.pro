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
