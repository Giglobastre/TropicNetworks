#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>


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

        ///setter
        void setSante(int val);
        void setCoeff(float val);
        void setNom(std::string val);
        void setNum(int val);
        void setActif(bool val);
        void setMarque(bool val);


        ///methodes
        bool est_adj_a(Sommet s);
    protected:

    private:
        int m_sante;
        float m_coeff;
        std::string m_nom;
        int m_numero;
        bool m_actif;
        bool m_marque;
};

#endif // SOMMET_H
