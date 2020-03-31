#ifndef MUR_H
#define MUR_H

#include "joueur.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>

class Mur
{
private:
    float positionX1;
    float positionY1;
    float positionX2;
    float positionY2;
    bool estPorte;
    char direction;
public:
    Mur(float x1, float y1, float x2, float y2, char d);
    virtual ~Mur();
    bool getEstPorte() {return estPorte;}
    void Display() const;
    void devenirPorte();
    bool collision(float x, float y, bool porteOuverte);
};

#endif // MUR_H
