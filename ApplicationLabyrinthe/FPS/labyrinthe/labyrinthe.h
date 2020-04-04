#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "carte.h"
#include "clef.h"
#include "joueur.h"
#include "mur.h"
#include "cell.h"
#include <vector>
#include <utility>

using namespace std;
using Point=pair<int,int>;

class Labyrinthe
{
private:
    vector<vector<Cell>> grid_;
    int largeur;
    int longueur;
    Carte carte;
    vector<Mur> murs;
    Clef clef;
    Joueur j1;
    bool porteOuverte = false;

    void addFrontier(Point p,list<Point> & frontier);
    void mark(Point p,list<Point> & frontier);
    list<Point> neighbors(Point p);
    Cell::Direction direction(Point f, Point t);

public:
    Labyrinthe(int width, int height);
    void recuperationClef();
    void display(GLuint* textures);
    void generate();
    void ouvrirPorte() {porteOuverte = true;}
    void deplacerJoueur(float x, float y);
    void deplacerJoueur(float pas, bool avance);
    void pivoterJoueur(bool sensTrigo) { j1.modifierOrientation(sensTrigo);}
    void desactiverClef() {clef.desactive();}
    bool collision();
    bool terminer();

    int getLargeur() {return largeur;}
    int getLongueur() {return longueur;}
    Joueur getJoueur() {return j1;}
};

#endif // LABYRINTHE_H
