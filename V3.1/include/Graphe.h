#ifndef GRAPHE_H
#define GRAPHE_H
#include "Arete.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include <allegro.h>
#include <ctime>


using namespace std;

class Graphe
{
    public:



        Graphe();
        Graphe(vector<vector<float> > adj);
        virtual ~Graphe();

        ///getters
        bool getPause();

        ///setters
        void setPause(bool val);

        ///méthodes
        void AllocOrdre(int m_ordre);
        void load(string nomfile); //Fonction récupérant les infos depuis le fichier du graphe
        void afficheInfos(); //Fonction affichant les infos récupérées (fonction de test)
        void destroy(); //Fonction "détruisant" un sommet du graphe (set la santé à 0)
        void save(string nomfile); //Fonction de sauvegarde
        //void forteconnexite(int s);

        void remplissage(int i , stack<int> &Stack);

        void dfs(int n);
        vector<Sommet>dfsbis(int n); // dfs qui retourne un vecteur qui stocke tous les sommets marque
        void getAdjacents();
        vector<vector<float> > getTranspose();
        void Kosaraju(); //forte connexite
        void affiche_graphe(std::string nomfile);
        int kuplet(int k , int n);
        void kconnexite();
        void Charger_images(std::string nomfile);
        void add(int DernierSommet);
        void supp(int DernierSommetsup);
        void croissance();
        void attendre(float temps);
        void pause();
        void affiche_boutons(BITMAP * page);

        //void forteconnexite();

    protected:

    private:

        //Attributs privés
        int m_ordre;
        int m_nbAretes;
        vector<Sommet> m_Sommets; //Liste des sommets
        vector<vector<float> > m_adjacences; //Matrice d'adjacence pondérée
        string m_nom;//Nom du fichier contenant le graphe
        bool m_pause;//Système en pause ou non
};

#endif // GRAPHE_H





