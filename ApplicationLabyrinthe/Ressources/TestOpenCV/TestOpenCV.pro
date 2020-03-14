#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T11:26:13
#
#-------------------------------------------------

QT       -= gui

TARGET = TestOpenCV
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_open_cv.cpp

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core420 \
    -lopencv_highgui420 \
    -lopencv_imgproc420 \
    -lopencv_imgcodecs420 \
    -lopencv_videoio420 \
    -lopencv_features2d420 \
    -lopencv_calib3d420

