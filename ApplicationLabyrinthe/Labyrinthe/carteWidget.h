    #ifndef CARTEWIDGET_H
#define CARTEWIDGET_H

#include "labyrinthe.h"
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>
#include <vector>

using namespace std;

// Classe dediee a l'affichage d'une scene OpenGL
class carteWidget : public QOpenGLWidget
{
    Q_OBJECT
    // Declarations des constantes
    const unsigned int WIN_WIDTH  = 1600;
    const unsigned int WIN_HEIGHT = 900;

public:

    // Constructeur & Destructeur
    carteWidget(QWidget * parent = nullptr);
    ~carteWidget() {delete this;}
    // Getters & Setters
    unsigned int getWidth() {return WIN_WIDTH;}
    unsigned int getHeight() {return WIN_HEIGHT;}
    float getCamX() {return cam_x;}
    float getCamY() {return cam_y;}
    float getCamZ() {return cam_z;}
    float getFixX() {return fix_x;}
    float getFixY() {return fix_y;}
    float getFixZ() {return fix_z;}
    Labyrinthe* getLabyrinthe() {return labyrinthe;}
    void setCamX(float newCamX) {cam_x = newCamX;}
    void setCamY(float newCamY) {cam_y = newCamY;}
    void setCamZ(float newCamZ) {cam_z = newCamZ;}
    void setFixX(float newFixX) {fix_x = newFixX;}
    void setFixY(float newFixY) {fix_y = newFixY;}
    void setFixZ(float newFixZ) {fix_z = newFixZ;}
    void setLabyrinthe(Labyrinthe* lab) {labyrinthe = lab;}

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

private:
    Labyrinthe* labyrinthe = new Labyrinthe(6,10);
    float cam_x = 1.5;
    float cam_y = 1.5;
    float cam_z = 1;
    float fix_x = cam_x+1;
    float fix_y = cam_y;
    float fix_z = cam_z;
    GLuint* texturesId;

public slots:
    // Fonction d'affichage
    void paintGL();

};

#endif // CARTEWIDGET_H
