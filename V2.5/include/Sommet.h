#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>
#include <allegro.h>


class Sommet
{
    public:
        Sommet();
        Sommet(int sante,float coeff ,std::string nom , int numero);
        ~Sommet();

        ///getter
        int getSante();
        float getCoeff();
        std::string getNom();
        int getNum();
        bool getActif();
        bool getMarque();
        int getPos_x();
        int getPos_y();
        BITMAP *getImage();

        ///setter
        void setSante(int val);
        void setCoeff(float val);
        void setNom(std::string val);
        void setNum(int val);
        void setActif(bool val);
        void setMarque(bool val);
        void setPos_x(int val);
        void setPos_y(int val);
        void setImage(std::string val);


        ///methodes
        bool est_adj_a(Sommet s);
    protected:

    private:
        int m_sante,m_x,m_y;
        float m_coeff;
        std::string m_nom;
        int m_numero;
        bool m_actif;
        bool m_marque;
        BITMAP *m_image;
};

#endif // SOMMET_H
