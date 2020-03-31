#include "mur.h"

// Déclaration de la constante d'épaisseur d'un mur
float a=0.2;

Mur::Mur(float x1, float y1, float x2, float y2, char d)
{
    positionX1 = x1;
    positionX2 = x2;
    positionY1 = y1;
    positionY2 = y2;
    estPorte = false;
    direction = d;
}

Mur::~Mur(){

}

void Mur::Display() const{

    // Affichage des murs E
    if( direction == 'E'){
        glBegin(GL_QUADS);
        glColor3ub(0, 0, 255); // Bleu

        glVertex3f(positionX1-a,positionY1+a,0.0f);
        glVertex3f(positionX1-a,positionY1-a,0.0f);
        glVertex3f(positionX2+a,positionY2-a,0.0f);
        glVertex3f(positionX2+a,positionY2+a,0.0f);

        glVertex3f(positionX1-a,positionY1+a,2.0f);
        glVertex3f(positionX1-a,positionY1-a,2.0f);
        glVertex3f(positionX2+a,positionY2-a,2.0f);
        glVertex3f(positionX2+a,positionY2+a,2.0f);

        glVertex3f(positionX1-a,positionY1+a,0.0f);
        glVertex3f(positionX1-a,positionY1-a,0.0f);
        glVertex3f(positionX1-a,positionY1-a,2.0f);
        glVertex3f(positionX1-a,positionY1+a,2.0f);

        glVertex3f(positionX2+a,positionY2-a,0.0f);
        glVertex3f(positionX2+a,positionY2+a,0.0f);
        glVertex3f(positionX2+a,positionY2+a,2.0f);
        glVertex3f(positionX2+a,positionY2-a,2.0f);

        glVertex3f(positionX1-a,positionY1-a,0.0f);
        glVertex3f(positionX2+a,positionY2-a,0.0f);
        glVertex3f(positionX2+a,positionY2-a,2.0f);
        glVertex3f(positionX1-a,positionY1-a,2.0f);

        glVertex3f(positionX1-a,positionY1+a,0.0f);
        glVertex3f(positionX2+a,positionY2+a,0.0f);
        glVertex3f(positionX2+a,positionY2+a,2.0f);
        glVertex3f(positionX1-a,positionY1+a,2.0f);

        glEnd();
    } else if (direction == 'S'){
        glBegin(GL_QUADS);
        glColor3ub(0, 0, 255); // Bleu

        glVertex3f(positionX1-a,positionY1-a,0.0f);
        glVertex3f(positionX1+a,positionY1-a,0.0f);
        glVertex3f(positionX2+a,positionY2+a,0.0f);
        glVertex3f(positionX2-a,positionY2+a,0.0f);

        glVertex3f(positionX1-a,positionY1-a,2.0f);
        glVertex3f(positionX1+a,positionY1-a,2.0f);
        glVertex3f(positionX2+a,positionY2+a,2.0f);
        glVertex3f(positionX2-a,positionY2+a,2.0f);

        glVertex3f(positionX1-a,positionY1-a,0.0f);
        glVertex3f(positionX1+a,positionY1-a,0.0f);
        glVertex3f(positionX1+a,positionY1-a,2.0f);
        glVertex3f(positionX1-a,positionY1-a,2.0f);

        glVertex3f(positionX2+a,positionY2+a,0.0f);
        glVertex3f(positionX2-a,positionY2+a,0.0f);
        glVertex3f(positionX2-a,positionY2+a,2.0f);
        glVertex3f(positionX2+a,positionY2+a,2.0f);

        glVertex3f(positionX1-a,positionY1-a,0.0f);
        glVertex3f(positionX2-a,positionY2+a,0.0f);
        glVertex3f(positionX2-a,positionY2+a,2.0f);
        glVertex3f(positionX1-a,positionY1-a,2.0f);

        glVertex3f(positionX1+a,positionY1-a,0.0f);
        glVertex3f(positionX2+a,positionY2+a,0.0f);
        glVertex3f(positionX2+a,positionY2+a,2.0f);
        glVertex3f(positionX1+a,positionY1-a,2.0f);

        glEnd();
    }
}

void Mur::devenirPorte(){
    estPorte = true;
}

bool Mur::collision(float x, float y, bool porteOuverte){
    bool autorise = true;
    if (!(estPorte && porteOuverte)){
        float b = 0.2 + a; // épaisseur du joueur et du mur
        if (x>positionX1-b && x<positionX2+b
         && y>positionY1-b && y<positionY2+b){
            autorise = false;
        }
    }
    return autorise;
}
