#ifndef INTERFACE_H
#define INTERFACE_H
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "modele.h"

class Interface : public QWidget {
        Q_OBJECT
    public:



        Interface(QWidget *parent = nullptr);



    private:



        Plateau plateau;
        QGridLayout* layout;

        QPushButton* casesBoutons[8][8];


        int selX = -1, selY = -1;
        void updateAffichage();



    private slots:



        void clic(int x,int y);
};
#endif

