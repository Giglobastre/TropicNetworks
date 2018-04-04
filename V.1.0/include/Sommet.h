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

        ///setter
        void setSante(int val);
        void setCoeff(float val);
        void setNom(std::string val);
        void setNum(int val);
        void setActif(bool val);


    protected:

    private:
        int m_sante;
        float m_coeff;
        std::string m_nom;
        int m_numero;
        bool m_actif;
};

#endif // SOMMET_H
