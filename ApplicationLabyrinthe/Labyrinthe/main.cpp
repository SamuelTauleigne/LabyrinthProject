#include "mainwindow.h"

#include <QApplication>
#include <ctime>
#include <myglwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*
    // Creation du widget opengl
    MyGLWidget glWidget;
    glWidget.show();
    */
    return a.exec();
}
