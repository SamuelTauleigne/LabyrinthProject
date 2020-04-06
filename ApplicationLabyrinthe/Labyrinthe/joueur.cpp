#include "joueur.h"
#include <math.h>

Joueur::Joueur(float x, float y)
{
    positionX = x;
    positionY = y;
    orientation = 0;
    sphere = gluNewQuadric();
}

void Joueur::modifierPosition(float x, float y){
    positionX = positionX + x;
    positionY = positionY + y;
}

void Joueur::modifierPosition(float pas, bool avance){
    float deplacementX = pas*cos(orientation);
    float deplacementY = pas*sin(orientation);
    if (avance){
        positionX = positionX + deplacementX;
        positionY = positionY + deplacementY;
    } else {
        positionX = positionX - deplacementX;
        positionY = positionY - deplacementY;
    }
}

void Joueur::modifierOrientation(bool sensTrigo){
    if (sensTrigo){
        orientation = orientation + M_PI/6;
    } else {
        orientation = orientation - M_PI/6;
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
