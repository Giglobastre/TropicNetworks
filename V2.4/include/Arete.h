#ifndef ARETE_H
#define ARETE_H
#include "Sommet.h"


class Arete
{
    public:
        Arete();
        virtual ~Arete();
        float getPoids();
        void setPoids(float val);


    protected:

    private:
        float m_poids;
        Sommet* m_s1 ;
        Sommet* m_s2;
};

#endif // ARETE_H
