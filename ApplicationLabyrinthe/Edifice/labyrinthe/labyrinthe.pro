
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



# nom de l'exe genere
TARGET 	  = Labyrinthe

# fichiers sources/headers/ressources
SOURCES += \
        carte.cpp \
        clef.cpp \
        joueur.cpp \
        labyrinthe.cpp \
        main.cpp \
        mur.cpp \
        myglwidget.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    carte.h \
    cell.h \
    clef.h \
    joueur.h \
    labyrinthe.h \
    mur.h \
    myglwidget.h


