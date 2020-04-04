#include "myglwidget.h"
#include "labyrinthe.h"
#include <GL/glu.h>
#include<QApplication>
#include <QDesktopWidget>
#include <cmath>
#include <random>

using namespace std;


// Declarations des constantes
const unsigned int WIN_WIDTH  = 1600;
const unsigned int WIN_HEIGHT = 900;

MyGLWidget::MyGLWidget(QWidget * parent){
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
    //glEnable(GL_LIGHTING);

    // Ajout des textures
    QImage murImg = QGLWidget::convertToGLFormat(QImage("C:/Users/jocel/OneDrive/Documents/Telecom St Etienne/FISE 2/Info/Labyrinthe/labyrinthe/labyrinthe/textures/mur2.jpg"));
    QImage solImg = QGLWidget::convertToGLFormat(QImage("C:/Users/jocel/OneDrive/Documents/Telecom St Etienne/FISE 2/Info/Labyrinthe/labyrinthe/labyrinthe/textures/sol.jpg"));
    QImage clefImg = QGLWidget::convertToGLFormat(QImage("C:/Users/jocel/OneDrive/Documents/Telecom St Etienne/FISE 2/Info/Labyrinthe/labyrinthe/labyrinthe/textures/TSE.png"));
    QImage plafondImg = QGLWidget::convertToGLFormat(QImage("C:/Users/jocel/OneDrive/Documents/Telecom St Etienne/FISE 2/Info/Labyrinthe/labyrinthe/labyrinthe/textures/plafond1.png"));

    texturesId = new GLuint[4];
    glGenTextures(11,texturesId);

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
    labyrinthe->display(texturesId);
    finir();

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

// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event){
    float pas = 0.125;
    switch (event->key()){
        case Qt::Key_Z :
            deplacerCamera(pas, labyrinthe->getJoueur().getOrientation(), true);
            labyrinthe->deplacerJoueur(pas, true);
            if (labyrinthe->collision()){
                deplacerCamera(pas, labyrinthe->getJoueur().getOrientation(), false);
                labyrinthe->deplacerJoueur(pas, false);
            }
            break;
        case Qt::Key_S :
            deplacerCamera(pas, labyrinthe->getJoueur().getOrientation(), false);
            labyrinthe->deplacerJoueur(pas, false);
            if (labyrinthe->collision()){
                deplacerCamera(pas, labyrinthe->getJoueur().getOrientation(), true);
                labyrinthe->deplacerJoueur(pas, true);
            }
            break;
        case Qt::Key_D :
            pivoterCamera(labyrinthe->getJoueur().getOrientation(), false);
            labyrinthe->pivoterJoueur(false);
            break;
        case Qt::Key_Q :
            pivoterCamera(labyrinthe->getJoueur().getOrientation(), true);
            labyrinthe->pivoterJoueur(true);
            break;
    }
    // Acceptation de l'événement et mise a jour de la scene
    event->accept();
    updateGL();

}
/*
// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event){
    float pas = 0.125;
    switch (event->key()){
        case Qt::Key_Z :
            if (fix_x == cam_x+1){
                cam_x=cam_x+pas;
                fix_x=fix_x+pas;
                labyrinthe->deplacerJoueur(pas,0);
                if (labyrinthe->collision()){
                    cam_x=cam_x-pas;
                    fix_x=fix_x-pas;
                    labyrinthe->deplacerJoueur(-pas,0);
                }
            } else if (fix_y == cam_y-1){
                cam_y=cam_y-pas;
                fix_y=fix_y-pas;
                labyrinthe->deplacerJoueur(0,-pas);
                if (labyrinthe->collision()){
                    cam_y=cam_y+pas;
                    fix_y=fix_y+pas;
                    labyrinthe->deplacerJoueur(0,pas);
                }
            } else if (fix_x == cam_x-1){
                cam_x=cam_x-pas;
                fix_x=fix_x-pas;
                labyrinthe->deplacerJoueur(-pas,0);
                if (labyrinthe->collision()){
                    cam_x=cam_x+pas;
                    fix_x=fix_x+pas;
                    labyrinthe->deplacerJoueur(pas,0);
                }
            } else if (fix_y == cam_y+1){
                cam_y=cam_y+pas;
                fix_y=fix_y+pas;
                labyrinthe->deplacerJoueur(0,pas);
                if (labyrinthe->collision()){
                    cam_y=cam_y-pas;
                    fix_y=fix_y-pas;
                    labyrinthe->deplacerJoueur(0,-pas);
                }
            }
            break;
        case Qt::Key_S :
            if (fix_x == cam_x+1){
                cam_x=cam_x-pas;
                fix_x=fix_x-pas;
                labyrinthe->deplacerJoueur(-pas,0);
                if (labyrinthe->collision()){
                    cam_x=cam_x+pas;
                    fix_x=fix_x+pas;
                    labyrinthe->deplacerJoueur(pas,0);
                }
            } else if (fix_y == cam_y-1){
                cam_y=cam_y+pas;
                fix_y=fix_y+pas;
                labyrinthe->deplacerJoueur(0,pas);
                if (labyrinthe->collision()){
                    cam_y=cam_y-pas;
                    fix_y=fix_y-pas;
                    labyrinthe->deplacerJoueur(0,-pas);
                }
            } else if (fix_x == cam_x-1){
                cam_x=cam_x+pas;
                fix_x=fix_x+pas;
                labyrinthe->deplacerJoueur(pas,0);
                if (labyrinthe->collision()){
                    cam_x=cam_x-pas;
                    fix_x=fix_x-pas;
                    labyrinthe->deplacerJoueur(-pas,0);
                }
            } else if (fix_y == cam_y+1){
                cam_y=cam_y-pas;
                fix_y=fix_y-pas;
                labyrinthe->deplacerJoueur(0,-pas);
                if (labyrinthe->collision()){
                    cam_y=cam_y+pas;
                    fix_y=fix_y+pas;
                    labyrinthe->deplacerJoueur(0,pas);
                }
            }
            break;
        case Qt::Key_D :
            if (fix_x == cam_x+1){
                fix_x--;
                fix_y--;
            } else if (fix_y == cam_y-1){
                fix_x--;
                fix_y++;
            } else if (fix_x == cam_x-1){
                fix_x++;
                fix_y++;
            } else if (fix_y == cam_y+1){
                fix_x++;
                fix_y--;
            }
            break;
        case Qt::Key_Q :
            if (fix_x == cam_x+1){
                fix_x--;
                fix_y++;
            } else if (fix_y == cam_y-1){
                fix_x++;
                fix_y++;
            } else if (fix_x == cam_x-1){
                fix_x++;
                fix_y--;
            } else if (fix_y == cam_y+1){
                fix_x--;
                fix_y--;
            }
            break;
    }
    // Acceptation de l'événement et mise a jour de la scene
    event->accept();
    updateGL();

}
*/

void MyGLWidget::finir(){
    if (labyrinthe->terminer()){
        this->close();
    }
}
