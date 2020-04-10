#include "carteWidget.h"
#include "labyrinthe.h"
#include <GL/glu.h>
#include<QApplication>
#include <QDesktopWidget>
#include <cmath>
#include <random>

#include <iostream>
using namespace std;




carteWidget::carteWidget(QWidget *parent){
    // Reglage de la taille/position
    resize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

}

// Fonction d'initialisation
void carteWidget::initializeGL() {
    // Reglage de la couleur de fond
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

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
void carteWidget::resizeGL(int width, int height){
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);


}

// Fonction d'affichage
void carteWidget::paintGL(){

    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT); // Effacer le buffer de couleur

    glClear(GL_DEPTH_BUFFER_BIT); // clear le Z buffer

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float largeur = labyrinthe->getLargeur();
    float longueur = labyrinthe->getLongueur();
    glOrtho(-(1+longueur/2), (1+longueur/2), -(1+largeur/2), (1+largeur/2), 1, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(longueur/2,largeur/2,5,
              longueur/2,largeur/2,0,
              0,1,0);

    labyrinthe->recuperationClef();
    labyrinthe->display(texturesId, true);


}
