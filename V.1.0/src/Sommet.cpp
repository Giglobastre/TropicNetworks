#include "Sommet.h"

Sommet::Sommet()
{
    m_sante=0;
    m_coeff=0;
    m_nom="";
    m_numero=0;
    m_actif = false;
}
Sommet::Sommet(int sante,float coeff ,std::string nom , int numero)
: m_sante(sante) , m_coeff(coeff) , m_nom(nom) , m_numero(numero)
{

}
Sommet::~Sommet()
{
    //dtor
}
///getters
int Sommet::getSante()
{
    return m_sante;
}
float Sommet::getCoeff()
{
    return m_coeff;
}
std::string Sommet::getNom()
{
    return m_nom;
}
int Sommet::getNum()
{
    return m_numero;
}

bool Sommet::getActif()
{
    return m_actif;
}

///setters
void Sommet::setSante(int val)
{
    m_sante=val;
}
void Sommet::setCoeff(float val)
{
    m_coeff=val;
}
void Sommet::setNom(std::string val)
{
    m_nom=val;
}
void Sommet::setNum(int val)
{
    m_numero=val;
}

void Sommet::setActif(bool val)
{
    m_actif = val;
}

