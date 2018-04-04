#include "Arete.h"

Arete::Arete()
{
    m_s1=new Sommet();
    m_s2=new Sommet();
}
Arete::~Arete()
{
    delete m_s1;
    delete m_s2;
}
float Arete::getpoids()
{
    return m_poids;
}
void Arete::setpoids(float val)
{
    m_poids=val;
}
