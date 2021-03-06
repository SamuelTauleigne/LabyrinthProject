#include "labyrinthe.h"
#include <ctime>

Labyrinthe::Labyrinthe(int width, int height)
        : grid_(height,vector<Cell>(width)), largeur(width), longueur(height), clef(0,0), j1(0,0)
{

}

void Labyrinthe::recuperationClef(){
    if (j1.distance(clef.getPositionX(), clef.getPositionY())<0.3){
        clef.desactive();
        ouvrirPorte();
    }
}

bool Labyrinthe::collision(){
    bool autorise = true;
    float jX = j1.getPositionX();
    float jY = j1.getPositionY();
    for (Mur mur : murs) {
        autorise = (autorise && mur.collision(jX, jY, porteOuverte));
    }
    return !autorise;
}

void Labyrinthe::deplacerJoueur(float x, float y) {
    j1.modifierPosition(x,y);
    if (collision()){
        j1.modifierPosition(-x,-y);
    }
}

bool Labyrinthe::terminer(){
    bool fin = false;
    float jX = j1.getPositionX();
    float jY = j1.getPositionY();
    if(!(jX>0 && jX<longueur && jY>0 && jY<largeur)){
        fin = true;
    }
}

void Labyrinthe::addFrontier(Point p,list<Point> & frontier){
    if (p.first>=0 && p.second>=0 && p.second<longueur && p.first<longueur
            && grid_[p.second][p.first].getValue()==0) {
        grid_[p.second][p.first].setValue(Cell::FRONTIER);
        frontier.push_back(p);
    }
}

void Labyrinthe::mark(Point p,list<Point> & frontier){
    grid_[p.second][p.first].setValue(Cell::MARKED);
    addFrontier(Point(p.first-1, p.second),frontier);
    addFrontier(Point(p.first+1, p.second),frontier);
    addFrontier(Point(p.first, p.second-1),frontier);
    addFrontier(Point(p.first, p.second+1),frontier);
}

list<Point> Labyrinthe::neighbors(Point p){
    list<Point> n;
    if (p.first>0 && grid_[p.second][p.first-1].getValue()==Cell::MARKED)
        n.push_back(Point(p.first-1, p.second));
    if (p.first+1<largeur && grid_[p.second][p.first+1].getValue()==Cell::MARKED)
        n.push_back(Point(p.first+1, p.second));
    if (p.second>0 && grid_[p.second-1][p.first].getValue()==Cell::MARKED)
        n.push_back(Point(p.first, p.second-1));
    if (p.second+1<longueur && grid_[p.second+1][p.first].getValue()==Cell::MARKED)
        n.push_back(Point(p.first, p.second+1));
    return n;
}

Cell::Direction Labyrinthe::direction(Point f, Point t){
    if (f.first<t.first) return Cell::E;
    else if (f.first>t.first) return Cell::W;
    else if (f.second<t.second) return Cell::S;
    else return Cell::N;
}

void Labyrinthe::display(){
    glBegin(GL_QUADS);
    glColor3ub(0, 255, 0);
    //sol du labyrinthe
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(longueur,0.0,0.0);
    glVertex3f(longueur,largeur,0.0);
    glVertex3f(0.0,largeur,0.0);
    //plafond du labyrinthe
    /*glVertex3f(0.0,0.0,2.0);
    glVertex3f(longueur,0.0,2.0);
    glVertex3f(longueur,largeur,2.0);
    glVertex3f(0.0,largeur,2.0);*/

    glEnd();

    j1.Display();

    if (clef.getEstActive())
        clef.Display();

    for (int i=0; i< murs.size(); i++){
        if (!(porteOuverte && murs[i].getEstPorte())){
            murs[i].Display();
        }
    }

}

void Labyrinthe::generate(){
    list<Point> frontier;

    // Initialize random generator
    srand (time(NULL));

    // Mark a random cell and add the frontier cells to the list
    mark(Point(rand() % largeur, rand() % longueur),frontier);


    while(!frontier.empty()) {

        // Take a random frontier cell f (from)
        auto randPos=frontier.begin();
        advance(randPos,rand() % frontier.size());
        Point f=*randPos;
        frontier.erase(randPos);

        // Take a random neighbor t (to) of that cell
        list<Point> n=neighbors(f);
        randPos=n.begin();
        advance(randPos,rand() % n.size());
        Point t=*randPos;

        // Carve a passage from f to t
        Cell::Direction d=direction(f,t);
        grid_[f.second][f.first].setFrontier(d,false);
        grid_[t.second][t.first].setFrontier(Cell::Direction((d+2)%4),false);

        // Mark the cell and add the frontier cells to the list
        mark(f,frontier);

    }
    // ajout du joueur
    j1.modifierPosition(rand()%longueur+0.5, rand()%largeur+0.5);
    // ajout de la clef
    clef = Clef(rand()%longueur+0.5, rand()%largeur+0.5);

    // ajout des murs extérieurs du labyrinthe
    for (int i=0;i<longueur;i++){
        Mur m1(i,0,i+1,0,'E');
        murs.push_back(m1);
        Mur m2(i,largeur,i+1,largeur,'E');
        murs.push_back(m2);
    }

    for (int j=0;j<largeur;j++){
        Mur m1(0,j,0,j+1,'S');
        murs.push_back(m1);
        Mur m2(longueur,j,longueur,j+1,'S');
        murs.push_back(m2);
    }

    // choix de la porte
    murs[rand()%murs.size()].devenirPorte();


    for (int i=0;i<longueur;i++) {
        for (int j=0;j<largeur;j++) {
            if (grid_[i][j].isFrontier(Cell::E) && j<largeur-1){
                Mur m(i,j+1,i+1,j+1,'E');
                murs.push_back(m);
            } if (grid_[i][j].isFrontier(Cell::S) && i<longueur-1){
                Mur m(i+1,j,i+1,j+1,'S');
                murs.push_back(m);
            }
        }

    }
}
