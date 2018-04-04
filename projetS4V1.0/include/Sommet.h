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
        int getsante();
        float getcoeff();
        std::string getnom();
        int getnumero();

        ///setter
        void setsante(int val);
        void setcoeff(float val);
        void setnom(std::string val);
        void setnumero(int val);


    protected:

    private:
        int m_sante;
        float m_coeff;
        std::string m_nom;
        int m_numero;
};

#endif // SOMMET_H
