#include "interface.h"
#include <QMessageBox>

Interface::Interface(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    // grille

    for(int i=0;i<8;i++)

        for(int j=0;j<8;j++){
            casesBoutons[i][j] = new QPushButton(this);
            casesBoutons[i][j]->setFixedSize(60,60);  // chaque cases est un bouton
            layout->addWidget(casesBoutons[i][j],i,j);
            connect(casesBoutons[i][j], &QPushButton::clicked,[=](){ clic(i,j); });
        }
    updateAffichage();
}

void Interface::updateAffichage(){

    // on se sert de la matrice du modele afin de contastemment etre en mesure d'afficher la piece à l'écran

    for(int i=0;i<8;i++)

        for(int j=0;j<8;j++){

            if(plateau.cases[i][j])

                casesBoutons[i][j]->setText(QString::fromStdString(plateau.cases[i][j]->symbole));


            else
                casesBoutons[i][j]->setText("");
        }

}

void Interface::clic(int x,int y)

{
    if(selX==-1){


        selX=x; selY=y; // clic numero 1
    }else{


        try {
            plateau.deplacer(selX,selY,x,y); // clic numero deux
        } catch(EchecMat&) {

            QMessageBox::information(this,"EchecMat","Echec et mat ! Partie réinitialisée.");
            plateau.reset();
        }
        selX=-1; selY=-1;
        updateAffichage();
    }
}
