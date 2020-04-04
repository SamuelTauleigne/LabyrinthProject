#ifndef JOUEUR_H
#define JOUEUR_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>

class Joueur
{
private:
    float positionX;
    float positionY;
    float orientation;
    GLUquadric* sphere;
public:
    Joueur(float x, float y);
    void modifierOrientation(bool sensTrigo);
    void modifierPosition(float x, float y);
    void modifierPosition(float pas, bool avance);
    void MajCamera();
    void Display() const;
    float distance(float x, float y);
    float getPositionX() {return positionX;}
    float getPositionY() {return positionY;}
    float getOrientation() {return orientation;}
};

#endif // JOUEUR_H
