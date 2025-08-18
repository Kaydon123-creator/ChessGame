#include "modele.h"
#include <cmath>

Plateau::Plateau() {


    cases.resize(8,std::vector<Piece*>(8,nullptr));


    initialiser();




}

Plateau::~Plateau() {


    for(auto& ligne : cases)
        for(auto& p : ligne) delete p;


    // on libere la mémoire des pieces
}

void Plateau::initialiser() {


    for(int i=0;i<8;i++){
        cases[1][i] = new Pion("P B");
        cases[6][i] = new Pion("P N");
    }
    cases[0][0] = new Tour("T B"); cases[0][7] = new Tour("T B");
    cases[7][0] = new Tour("T N"); cases[7][7] = new Tour("T N");
    cases[0][1] = new Cavalier("C B"); cases[0][6] = new Cavalier("C B");
    cases[7][1] = new Cavalier("C N"); cases[7][6] = new Cavalier("C N");
    cases[0][2] = new Fou("F B"); cases[0][5] = new Fou("F B");
    cases[7][2] = new Fou("F N"); cases[7][5] = new Fou("F N");
    cases[0][3] = new Dame("D B"); cases[7][3] = new Dame("D N");
    cases[0][4] = new Roi("R B"); cases[7][4] = new Roi("R N");
}



bool Plateau::deplacer(int x1,int y1,int x2,int y2){

    if(!cases[x1][y1]) return false;
    if(!cases[x1][y1]->deplacementValide(x1,y1,x2,y2,cases)) return false;
    delete cases[x2][y2];


    cases[x2][y2] = cases[x1][y1];  //on interchange les cases

    cases[x1][y1] = nullptr;

    if(roiNoirEnEchec() || roiBlancEnEchec()) throw EchecMat();
    return true;
}

void Plateau::reset(){
        for(auto& ligne : cases)

            for(auto& p : ligne){ delete p; p=nullptr; }

        initialiser();
}

bool Plateau::roiNoirEnEchec(){ return false; } // a completer
bool Plateau::roiBlancEnEchec(){ return false; } // a completer

bool Pion::deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases){
            int sens = symbole[2]=='B'? 1 : -1;

            if(x2==x1+sens && y2==y1 && !cases[x2][y2]) return true;

            if(x2==x1+sens && std::abs(y2-y1)==1 && cases[x2][y2]) return true;

            return false;
}

bool Tour::deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases){


    if(x1!=x2 && y1!=y2) return false;


    int dx = (x2-x1)? (x2>x1?1:-1):0;
    int dy = (y2-y1)? (y2>y1?1:-1):0;

    int nx=x1+dx, ny=y1+dy;


    while(nx!=x2 || ny!=y2){

        if(cases[nx][ny]) return false;


        nx+=dx; ny+=dy;
    }


    return true;
}

bool Cavalier::deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &){

        int dx=std::abs(x2-x1), dy=std::abs(y2-y1);

        return (dx==2 && dy==1)||(dx==1 && dy==2);
}

bool Fou::deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases){

    if(std::abs(x2-x1)!=std::abs(y2-y1)) return false;
    int dx=(x2>x1?1:-1), dy=(y2>y1?1:-1);
    int nx=x1+dx, ny=y1+dy;
    while(nx!=x2 && ny!=y2){
        if(cases[nx][ny]) return false;
        nx+=dx; ny+=dy;
    }
    return true;
}

bool Dame::deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases){

    Tour t(symbole); Fou f(symbole);
    return t.deplacementValide(x1,y1,x2,y2,cases) || f.deplacementValide(x1,y1,x2,y2,cases);
}

bool Roi::deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &){
    return std::abs(x2-x1)<=1 && std::abs(y2-y1)<=1;
}
