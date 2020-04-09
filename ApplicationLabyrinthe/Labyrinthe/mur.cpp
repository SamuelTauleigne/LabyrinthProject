#include "mur.h"

// Déclaration de la constante d'épaisseur d'un mur
float a=0.15;

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

void Mur::Display(GLuint* textures) const{

    // Affichage des murs E
    if( direction == 'E'){
        glColor3ub(255, 255, 255); // Blanc
        GLfloat reflet[] = {double(255)/255,double(255)/255,double(255)/255,1.0};
        GLfloat pasReflet[] = {0.0,0.0,0.0,1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, reflet);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, reflet);
        glMaterialfv(GL_FRONT, GL_EMISSION, pasReflet );

        glBindTexture(GL_TEXTURE_2D,textures[2]);
        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1+a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX1-a,positionY1-a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2+a,positionY2-a,0.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX2+a,positionY2+a,0.0f);

        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1+a,2.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX1-a,positionY1-a,2.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2+a,positionY2-a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX2+a,positionY2+a,2.0f);
        glEnd();

        glBindTexture(GL_TEXTURE_2D,textures[0]);
        glBegin(GL_QUADS);
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1+a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX1-a,positionY1-a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX1-a,positionY1-a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX1-a,positionY1+a,2.0f);

        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0, 0); glVertex3f(positionX2+a,positionY2-a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX2+a,positionY2+a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2+a,positionY2+a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX2+a,positionY2-a,2.0f);

        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1-a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX2+a,positionY2-a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2+a,positionY2-a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX1-a,positionY1-a,2.0f);

        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1+a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX2+a,positionY2+a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2+a,positionY2+a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX1-a,positionY1+a,2.0f);

        glEnd();
    } else if (direction == 'S'){
        glColor3ub(255, 255, 255); // Blanc

        glBindTexture(GL_TEXTURE_2D,textures[2]);
        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1-a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX1+a,positionY1-a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2+a,positionY2+a,0.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX2-a,positionY2+a,0.0f);

        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1-a,2.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX1+a,positionY1-a,2.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2+a,positionY2+a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX2-a,positionY2+a,2.0f);
        glEnd();

        glBindTexture(GL_TEXTURE_2D,textures[0]);
        glBegin(GL_QUADS);
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1-a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX1+a,positionY1-a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX1+a,positionY1-a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX1-a,positionY1-a,2.0f);

        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0, 0); glVertex3f(positionX2+a,positionY2+a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX2-a,positionY2+a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2-a,positionY2+a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX2+a,positionY2+a,2.0f);

        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1-a,positionY1-a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX2-a,positionY2+a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2-a,positionY2+a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX1-a,positionY1-a,2.0f);

        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(0, 0); glVertex3f(positionX1+a,positionY1-a,0.0f);
        glTexCoord2f(1, 0); glVertex3f(positionX2+a,positionY2+a,0.0f);
        glTexCoord2f(1, 1); glVertex3f(positionX2+a,positionY2+a,2.0f);
        glTexCoord2f(0, 1); glVertex3f(positionX1+a,positionY1-a,2.0f);

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
