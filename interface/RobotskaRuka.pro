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

LIBS     += -lopencv_calib3d \
            -lopencv_contrib \
            -lopencv_core \
            -lopencv_features2d \
            -lopencv_flann \
            -lopencv_gpu \
            -lopencv_highgui \
            -lopencv_imgproc \
            -lopencv_legacy \
            -lopencv_ml \
            -lopencv_objdetect \
            -lopencv_ocl \
            -lopencv_photo \
            -lopencv_stitching \
            -lopencv_superres \
            -lopencv_ts \
            -lopencv_video \
            -lopencv_videostab
