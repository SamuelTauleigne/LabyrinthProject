#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "carte.h"
#include "clef.h"
#include "joueur.h"
#include "mur.h"
#include "cell.h"
#include <vector>
#include <utility>
#include <QPoint>

using namespace std;
// using Point=pair<int,int>;

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

    void addFrontier(pair<int,int> p, list<pair<int,int>> &frontier);
    void mark(pair<int,int> p,list<pair<int,int>> & frontier);
    list<pair<int,int>> neighbors(pair<int,int> p);
    Cell::Direction direction(pair<int,int> f, pair<int,int> t);

public:
    Labyrinthe(int width, int height);
    void recuperationClef();
    void display();
    void generate();
    void ouvrirPorte() {porteOuverte = true;}
    void deplacerJoueur(float x, float y);
    void desactiverClef() {clef.desactive();}
    bool collision();
    bool terminer();

    Joueur getJoueur() {return j1;}
};

#endif // LABYRINTHE_H
