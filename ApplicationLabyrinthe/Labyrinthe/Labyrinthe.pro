# configuration Qt
QT       += core gui opengl widgets
TEMPLATE  = app

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    carteWidget.cpp \
    clef.cpp \
    joueur.cpp \
    labyrinthe.cpp \
    main.cpp \
    mainwindow.cpp \
    mur.cpp \
    myglwidget.cpp \
    webcam.cpp

HEADERS += \
    carteWidget.h \
    cell.h \
    clef.h \
    joueur.h \
    labyrinthe.h \
    mainwindow.h \
    mur.h \
    myglwidget.h \
    webcam.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#INCLUDEPATH +=$$(OPENCV_DIR)\include # Samuel
INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include # Jocelyn

LIBS += -L$$(OPENCV_DIR)\lib \ # Jocelyn
#LIBS += -L$$(OPENCV_DIR)\x64\mingw\lib \ #Samuel
    -lopencv_core420 \
    -lopencv_highgui420 \
    -lopencv_imgproc420 \
    -lopencv_imgcodecs420 \
    -lopencv_videoio420 \
    -lopencv_features2d420 \
    -lopencv_calib3d420 \
    -lopencv_objdetect420
