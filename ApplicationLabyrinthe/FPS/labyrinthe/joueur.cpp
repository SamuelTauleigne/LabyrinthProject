#include "joueur.h"
#include <math.h>

Joueur::Joueur(float x, float y)
{
    positionX = x;
    positionY = y;
    orientation = 0;
    sphere = gluNewQuadric();
}

void Joueur::modifierOrientation(){

}

void Joueur::modifierPosition(float x, float y){
    positionX = positionX + x;
    positionY = positionY + y;
}

void Joueur::modifierPosition(bool avance){
    float deplacementX = cos(orientation);
    float deplacementY = sin(orientation);
    if (avance){
        positionX = positionX + deplacementX;
        positionY = positionY + deplacementY;
    } else {
        positionX = positionX - deplacementX;
        positionY = positionY - deplacementY;
    }
}

void Joueur::MajCamera(){

}

void Joueur::Display() const{
    glPushMatrix();
    glTranslated(positionX, positionY, 1);
    glColor3ub(255, 255, 0); // Rouge
    gluQuadricDrawStyle(sphere,GLU_FILL);
    gluSphere(sphere, 0.2, 20, 20);
    glPopMatrix();
}

float Joueur::distance(float x, float y){
    return sqrt((positionX-x)*(positionX-x) + (positionY-y)*(positionY-y));
}
