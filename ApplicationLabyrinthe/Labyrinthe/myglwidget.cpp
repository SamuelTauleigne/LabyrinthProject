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
    glEnable(GL_TEXTURE_2D);

    // Activation de l'éclairage
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    GLfloat ambiantColor[] =  {0.5,0.5,0.5,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiantColor);
    GLfloat diffuseColor[] =  {1.0,1.0,0.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    GLfloat positionLight[] =  {0.0,0.0,0.5,0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight);

    // Ajout des textures
    QImage murImg = QGLWidget::convertToGLFormat(QImage("../Labyrinthe/textures/mur2.jpg"));
    QImage solImg = QGLWidget::convertToGLFormat(QImage("../Labyrinthe/textures/sol.jpg"));
    QImage clefImg = QGLWidget::convertToGLFormat(QImage("../Labyrinthe/textures/TSE.png"));
    QImage plafondImg = QGLWidget::convertToGLFormat(QImage("../Labyrinthe/textures/plafond1.png"));
    QImage blancImg = QGLWidget::convertToGLFormat(QImage("../Labyrinthe/textures/blanc.jpg"));

    texturesId = new GLuint[5];
    glGenTextures(5,texturesId);

    glBindTexture(GL_TEXTURE_2D,texturesId[0]);
    glTexImage2D(GL_TEXTURE_2D,0, 4,murImg.width(),murImg.height(),0,GL_RGBA, GL_UNSIGNED_BYTE, murImg.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,texturesId[1]);
    glTexImage2D(GL_TEXTURE_2D,0, 4,solImg.width(),solImg.height(),0,GL_RGBA, GL_UNSIGNED_BYTE, solImg.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,texturesId[2]);
    glTexImage2D(GL_TEXTURE_2D,0, 4,plafondImg.width(),plafondImg.height(),0,GL_RGBA, GL_UNSIGNED_BYTE, plafondImg.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,texturesId[3]);
    glTexImage2D(GL_TEXTURE_2D,0, 4,clefImg.width(),clefImg.height(),0,GL_RGBA, GL_UNSIGNED_BYTE, clefImg.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,texturesId[4]);
    glTexImage2D(GL_TEXTURE_2D,0, 4,blancImg.width(),blancImg.height(),0,GL_RGBA, GL_UNSIGNED_BYTE, blancImg.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    labyrinthe->generate();

    cam_x = labyrinthe->getJoueur().getPositionX();
    cam_y = labyrinthe->getJoueur().getPositionY();
    fix_x = cam_x+1;
    fix_y = cam_y;
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

    gluPerspective(80.0f, ((float)WIN_WIDTH)/WIN_HEIGHT, 0.2f, 20.0f);
    //glFrustum(-10, 10, -10, 10, 0.1, 4);
    //glOrtho(-10, 10, -10, 10, 1, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
// /*
    gluLookAt(cam_x, cam_y, cam_z, // position de la caméra
    fix_x, fix_y, fix_z, // position du point que fixe la caméra
    0, 0, 1); // vecteur vertical
/*
    gluLookAt(5,3,5,
              5,3,0,
              0,1,0);
*/
    labyrinthe->recuperationClef();
    labyrinthe->display(texturesId, false);
    //finir();

}

void MyGLWidget::deplacerCamera(float pas, float orientation, bool avance){
    float deplacementX = pas*cos(orientation);
    float deplacementY = pas*sin(orientation);
    if (avance){
        cam_x = cam_x + deplacementX;
        cam_y = cam_y + deplacementY;
        fix_x = fix_x + deplacementX;
        fix_y = fix_y + deplacementY;
    } else {
        cam_x = cam_x - deplacementX;
        cam_y = cam_y - deplacementY;
        fix_x = fix_x - deplacementX;
        fix_y = fix_y - deplacementY;
    }
}

void MyGLWidget::pivoterCamera(float orientation, bool sensTrigo){
    float deplacementX = cos(orientation);
    float deplacementY = sin(orientation);
    fix_x = cam_x;
    fix_y = cam_y;
    if (sensTrigo){
        deplacementX = cos(orientation + M_PI/6);
        deplacementY = sin(orientation + M_PI/6);
        fix_x = fix_x + deplacementX;
        fix_y = fix_y + deplacementY;
    } else {
        deplacementX = cos(orientation - M_PI/6);
        deplacementY = sin(orientation - M_PI/6);
        fix_x = fix_x + deplacementX;
        fix_y = fix_y + deplacementY;
    }
}

void MyGLWidget::genererLabyrinthe(){
    labyrinthe->generate();
    cam_x = labyrinthe->getJoueur().getPositionX();
    cam_y = labyrinthe->getJoueur().getPositionY();
    fix_x = cam_x+1;
    fix_y = cam_y;
}
