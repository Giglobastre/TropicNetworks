#ifndef ARETE_H
#define ARETE_H
#include "Sommet.h"


class Arete
{
    public:
        Arete();
        virtual ~Arete();
        float getpoids();
        void setpoids(float val);


    protected:

    private:
        float m_poids;
        Sommet* m_s1 ;
        Sommet* m_s2;
};

#endif // ARETE_H
