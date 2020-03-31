#include "clef.h"

Clef::Clef(float x, float y)
{
    positionX = x;
    positionY = y;
    estActive = true;
    sphere = gluNewQuadric();
}

Clef::~Clef(){
    // Destruction de la quadrique
    //gluDeleteQuadric(this->sphere);
}

void Clef::Display() const{

    glPushMatrix();
    //glLoadIdentity();
    glTranslated(positionX, positionY, 1);
    glColor3ub(255, 0, 0); // Rouge
    gluQuadricDrawStyle(sphere,GLU_FILL);
    gluSphere(sphere, 0.2, 20, 20);
    glLoadIdentity();
    glPopMatrix();
}

void Clef::recuperation(Joueur j1){
    if (j1.distance(positionX, positionY)<0.3){
        estActive = false;
        //labyrinthe->ouvrirPorte();
        delete this;
    }
}

