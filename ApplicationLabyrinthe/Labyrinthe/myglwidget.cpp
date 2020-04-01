#include "myglwidget.h"
#include "labyrinthe.h"
#include <GL/glu.h>
#include<QApplication>
#include <QDesktopWidget>
#include <cmath>
#include <random>

#include <iostream>
using namespace std;


// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;

MyGLWidget::MyGLWidget(QWidget *parent){
    // Reglage de la taille/position
    resize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

}

// Fonction d'initialisation
void MyGLWidget::initializeGL() {
    // Reglage de la couleur de fond
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);

    // Activation de l'éclairage
    //glEnable(GL_LIGHTING);

    labyrinthe->generate();
}

// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height){
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);


}

// Fonction d'affichage
void MyGLWidget::paintGL(){

    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT); // Effacer le buffer de couleur

    glClear(GL_DEPTH_BUFFER_BIT); // clear le Z buffer

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //gluPerspective(80.0f, ((float)WIN_WIDTH)/WIN_HEIGHT, 0.3f, 20.0f);

    glOrtho(-10, 15, -10, 10, 1, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
/*
    cam_x = labyrinthe->getJoueur().getPositionX();
    cam_y = labyrinthe->getJoueur().getPositionY();
    gluLookAt(cam_x, cam_y, cam_z, // position de la caméra
    fix_x, fix_y, fix_z, // position du point que fixe la caméra
    0, 0, 1); // vecteur vertical
*/
    gluLookAt(5,3,8,
              5,3,0,
              0,1,0);

    labyrinthe->recuperationClef();
    labyrinthe->display();
    finir();

}

void MyGLWidget::finir(){
    if (labyrinthe->terminer()){
        this->close();
    }
}
