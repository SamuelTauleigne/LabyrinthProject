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
    // Getters & Setters
    float getCamX() {return cam_x;}
    float getCamY() {return cam_y;}
    float getCamZ() {return cam_z;}
    float getFixX() {return fix_x;}
    float getFixY() {return fix_y;}
    float getFixZ() {return fix_z;}
    float setCamX(float newCamX) {cam_x = newCamX;}
    float setCamY(float newCamY) {cam_y = newCamY;}
    float setCamZ(float newCamZ) {cam_z = newCamZ;}
    float setFixX(float newFixX) {fix_x = newFixX;}
    float setFixY(float newFixY) {fix_y = newFixY;}
    float setFixZ(float newFixZ) {fix_z = newFixZ;}
    Labyrinthe* getLabyrinth() {return labyrinthe;}

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
