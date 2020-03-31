#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "labyrinthe.h"
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>
#include <vector>

using namespace std;

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);
    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);





private:

    Labyrinthe* labyrinthe = new Labyrinthe(6,10);
    // Coordonnées à supprimer par la suite (juste ppiur tester les déplacements pour le déggogage)
    float cam_x = 1.5;
    float cam_y = 1.5;
    float cam_z = 1;
    float fix_x = cam_x+1;
    float fix_y = cam_y;
    float fix_z = cam_z;
    bool zBuffer = true;

    void finir();

public slots:
    // Fonction d'affichage
    void paintGL();

};

#endif // MYGLWIDGET_H
