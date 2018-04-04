#ifndef GRAPHE_H
#define GRAPHE_H
#include "Arete.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Graphe
{
    public:
        Graphe();
        virtual ~Graphe();
        void AllocOrdre(int m_ordre);
        void load(string nomfile); //Fonction r�cup�rant les infos depuis le fichier du graphe
        void afficheInfos(); //Fonction affichant les infos r�cup�r�es (fonction de test)
        void destroy(int n); //Fonction "d�truisant" un sommet du graphe (set la sant� � 0)
        void save(string nomfile); //Fonction de sauvegarde
        int temps();


    protected:

    private:

        //Attributs priv�s
        int m_ordre;
        int m_nbAretes;
        vector<Sommet> m_Sommets; //Liste des sommets
        vector<vector<float> > m_adjacences; //Matrice d'adjacence pond�r�e
        string m_nom;//Nom du fichier contenant le graphe
};

#endif // GRAPHE_H




