#include "Sommet.h"

Sommet::Sommet()
{
    m_sante=0;
    m_coeff=0;
    m_nom="";
    m_numero=0;
    m_actif = false;
    m_marque=false;
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
int Sommet::getPos_x()
{
    return m_x;
}
int Sommet::getPos_y()
{
    return m_y;
}

bool Sommet::getActif()
{
    return m_actif;
}
bool Sommet::getMarque()
{
    return m_marque;
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
void Sommet::setMarque(bool val)
{
    m_marque = true;
}
bool Sommet::est_adj_a(Sommet s)
{
    return true;
}
void Sommet::setPos_x(int val)
{
    m_x=val;
}
void Sommet::setPos_y(int val)
{
    m_y=val;
}
void Sommet::affiche(BITMAP * page)
{
    string nom_image;
    BITMAP * image;

    nom_image = "Images/";
    nom_image += m_nom;
    nom_image += ".bmp";

    image = load_bitmap(nom_image.c_str(), NULL);

    if(!image)
    {
        allegro_message("Probleme de chargement de l'image");
    }
    setActif(true);
   // draw_sprite(page,image,getPos_x()-100,getPos_y()-100);
}
