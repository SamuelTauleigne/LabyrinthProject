#ifndef CLEF_H
#define CLEF_H

#include "joueur.h"
#include "mur.h"


class Clef
{
private :
    float positionX;
    float positionY;
    bool estActive;
    GLUquadric* sphere;
public:
    Clef(float x, float y);
    virtual ~Clef();
    void Display() const;
    void recuperation(Joueur j1);
    float getPositionX() {return positionX;}
    float getPositionY() {return positionY;}
    bool getEstActive() {return estActive;}
    void desactive() {estActive = false;}
};

#endif // CLEF_H
