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

void Labyrinthe::deplacerJoueur(float x, float y){
    j1.modifierPosition(x,y);
}

void Labyrinthe::deplacerJoueur(float pas, bool avance){
    j1.modifierPosition(pas, avance);
}

bool Labyrinthe::terminer(){
    bool fin = false;
    float jX = j1.getPositionX();
    float jY = j1.getPositionY();
    if(!(jX>0 && jX<longueur && jY>0 && jY<largeur)){
        fin = true;
    }
    return fin;
}

void Labyrinthe::addFrontier(PointGraph p,list<PointGraph> & frontier){
    if (p.first>=0 && p.second>=0 && p.second<longueur && p.first<longueur
            && grid_[p.second][p.first].getValue()==0) {
        grid_[p.second][p.first].setValue(Cell::FRONTIER);
        frontier.push_back(p);
    }
}

void Labyrinthe::mark(PointGraph p,list<PointGraph> & frontier){
    grid_[p.second][p.first].setValue(Cell::MARKED);
    addFrontier(PointGraph(p.first-1, p.second),frontier);
    addFrontier(PointGraph(p.first+1, p.second),frontier);
    addFrontier(PointGraph(p.first, p.second-1),frontier);
    addFrontier(PointGraph(p.first, p.second+1),frontier);
}

list<PointGraph> Labyrinthe::neighbors(PointGraph p){
    list<PointGraph> n;
    if (p.first>0 && grid_[p.second][p.first-1].getValue()==Cell::MARKED)
        n.push_back(PointGraph(p.first-1, p.second));
    if (p.first+1<largeur && grid_[p.second][p.first+1].getValue()==Cell::MARKED)
        n.push_back(PointGraph(p.first+1, p.second));
    if (p.second>0 && grid_[p.second-1][p.first].getValue()==Cell::MARKED)
        n.push_back(PointGraph(p.first, p.second-1));
    if (p.second+1<longueur && grid_[p.second+1][p.first].getValue()==Cell::MARKED)
        n.push_back(PointGraph(p.first, p.second+1));
    return n;
}

Cell::Direction Labyrinthe::direction(PointGraph f, PointGraph t){
    if (f.first<t.first) return Cell::E;
    else if (f.first>t.first) return Cell::W;
    else if (f.second<t.second) return Cell::S;
    else return Cell::N;
}

void Labyrinthe::display(GLuint* textures){
    glBindTexture(GL_TEXTURE_2D,textures[1]);
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    //sol du labyrinthe
    glTexCoord2f(0, 0); glVertex3f(0.0,0.0,0.0);
    glTexCoord2f(longueur, 0); glVertex3f(longueur,0.0,0.0);
    glTexCoord2f(longueur, largeur); glVertex3f(longueur,largeur,0.0);
    glTexCoord2f(0, largeur); glVertex3f(0.0,largeur,0.0);
    glEnd();
    //plafond du labyrinthe
    glBindTexture(GL_TEXTURE_2D,textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0.0,0.0,2.0);
    glTexCoord2f(longueur, 0); glVertex3f(longueur,0.0,2.0);
    glTexCoord2f(longueur, largeur); glVertex3f(longueur,largeur,2.0);
    glTexCoord2f(0, largeur); glVertex3f(0.0,largeur,2.0);
    glEnd();

    j1.Display();

    if (clef.getEstActive()){
        glBindTexture(GL_TEXTURE_2D,textures[3]);
        clef.Display();
    }

    for (int i=0; i< murs.size(); i++){
        if (!(porteOuverte && murs[i].getEstPorte())){
            glBindTexture(GL_TEXTURE_2D,textures[0]);
            murs[i].Display();
        }
    }

}

void Labyrinthe::display(){
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    //sol du labyrinthe
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(longueur,0.0,0.0);
    glVertex3f(longueur,largeur,0.0);
   glVertex3f(0.0,largeur,0.0);
    glEnd();
    //plafond du labyrinthe
    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,2.0);
    glVertex3f(longueur,0.0,2.0);
    glVertex3f(longueur,largeur,2.0);
    glVertex3f(0.0,largeur,2.0);
    glEnd();

    j1.Display();

    if (clef.getEstActive()){
        clef.Display();
    }

    for (int i=0; i< murs.size(); i++){
        if (!(porteOuverte && murs[i].getEstPorte())){
            murs[i].Display();
        }
    }

}

void Labyrinthe::generate(){
    list<PointGraph> frontier;

    // Initialize random generator
    srand (time(NULL));

    // Mark a random cell and add the frontier cells to the list
    mark(PointGraph(rand() % largeur, rand() % longueur),frontier);


    while(!frontier.empty()) {

        // Take a random frontier cell f (from)
        auto randPos=frontier.begin();
        advance(randPos,rand() % frontier.size());
        PointGraph f=*randPos;
        frontier.erase(randPos);

        // Take a random neighbor t (to) of that cell
        list<PointGraph> n=neighbors(f);
        randPos=n.begin();
        advance(randPos,rand() % n.size());
        PointGraph t=*randPos;

        // Carve a passage from f to t
        Cell::Direction d=direction(f,t);
        grid_[f.second][f.first].setFrontier(d,false);
        grid_[t.second][t.first].setFrontier(Cell::Direction((d+2)%4),false);

        // Mark the cell and add the frontier cells to the list
        mark(f,frontier);

    }
    // ajout du joueur
    float jX = rand()%longueur+0.5;
    float jY = rand()%largeur+0.5;
    j1.modifierPosition(jX, jY);
    // ajout de la clef
    clef = Clef(rand()%longueur+0.5, rand()%largeur+0.5);
    while (clef.getPositionX()==jX && clef.getPositionY()==jY){
        clef = Clef(rand()%longueur+0.5, rand()%largeur+0.5);
    }

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
