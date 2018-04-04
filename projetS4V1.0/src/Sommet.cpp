#include "Sommet.h"

Sommet::Sommet()
{
    m_sante=0;
    m_coeff=0;
    m_nom="";
    m_numero=0;
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
int Sommet::getsante()
{
    return m_sante;
}
float Sommet::getcoeff()
{
    return m_coeff;
}
std::string Sommet::getnom()
{
    return m_nom;
}
int Sommet::getnumero()
{
    return m_numero;
}

///setters
void Sommet::setsante(int val)
{
    m_sante=val;
}
void Sommet::setcoeff(float val)
{
    m_coeff=val;
}
void Sommet::setnom(std::string val)
{
    m_nom=val;
}
void Sommet::setnumero(int val)
{
    m_numero=val;
}
