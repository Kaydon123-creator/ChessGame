#ifndef MODELE_H
#define MODELE_H
#include <vector>
#include <string>
#include <stdexcept>

class EchecMat : public std::exception {
    public:
        const char* what() const noexcept override { return "C'est fini, bravo au gagnant!!!! "; }
};





// logique des pieces : leurs deplacements

class Piece {


    public:


        std::string symbole;
        Piece(const std::string& s) : symbole(s) {}
        virtual ~Piece() {}
        virtual bool deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases) = 0;
};

class Pion : public Piece {
    public:
        Pion(const std::string& s) : Piece(s) {}
        bool deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases) override;
};





class Tour : public Piece {



    public:
        Tour(const std::string& s) : Piece(s) {}


        bool deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases) override;


};

class Cavalier : public Piece {
    public:
        Cavalier(const std::string& s) : Piece(s) {}


        bool deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases) override;


};

class Fou : public Piece {


    public:



        Fou(const std::string& s) : Piece(s) {}


        bool deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases) override;


};

class Dame : public Piece {


    public:


        Dame(const std::string& s) : Piece(s) {}
        bool deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases) override;
};



class Roi : public Piece {


    public:


        Roi(const std::string& s) : Piece(s) {}
        bool deplacementValide(int x1,int y1,int x2,int y2,std::vector<std::vector<Piece*>> &cases) override;
};

class Plateau {
    public:


        std::vector<std::vector<Piece*>> cases;

        Plateau();
        ~Plateau();



        bool deplacer(int x1, int y1, int x2, int y2);


        void reset();

    private:


        void initialiser();

        bool roiNoirEnEchec();
        bool roiBlancEnEchec();
};

#endif
