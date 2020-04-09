#include "joueur.h"
#include <math.h>

Joueur::Joueur(float x, float y)
{
    positionX = x;
    positionY = y;
    sphere = gluNewQuadric();
}

void Joueur::modifierOrientation(){

}

void Joueur::modifierPosition(float x, float y){
    positionX = positionX + x;
    positionY = positionY + y;
}

void Joueur::MajCamera(){

}

void Joueur::Display() const{
    glPushMatrix();
    //glLoadIdentity();
    glTranslated(positionX, positionY, 1);
    glColor3ub(255, 255, 0); // Rouge
    gluQuadricDrawStyle(sphere,GLU_FILL);
    gluSphere(sphere, 0.2, 20, 20);
    glLoadIdentity();
    glPopMatrix();
}

float Joueur::distance(float x, float y){
    return sqrt((positionX-x)*(positionX-x) + (positionY-y)*(positionY-y));
}
