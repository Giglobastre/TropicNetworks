#include "Graphe.h"
#include <stack>
using namespace std;

Graphe::Graphe()
{
    m_ordre = 0;
    m_nbAretes = 0;
    string nom = "";
}
Graphe::Graphe(vector<vector<float> > adj)
{
    m_adjacences=adj;
}
Graphe::~Graphe()
{
}

void Graphe::AllocOrdre(int m_ordre)
{
    for(int i=0 ; i < m_ordre ; i ++)
    {
        m_adjacences.push_back(vector<float>(m_ordre));
    }
}

//Un sommet détruit a sa santé à 0
void Graphe::destroy()
{
    while(!mouse_b & 1)
    {
        for(int i =0 ; i < m_ordre ; i++)
        {
            if(mouse_b &1 && mouse_x>m_Sommets[i].getPos_x()-38 && mouse_x<m_Sommets[i].getPos_x()+38 && mouse_y>m_Sommets[i].getPos_y()-38 && mouse_y<m_Sommets[i].getPos_y()+38)
            {
                m_Sommets[i].setSante(0);
                m_Sommets[i].setActif(false);
                cout << "Destruction du sommet "<< m_Sommets[i].getNom() << " !"<< endl << endl;
            }
        }
    }
}

//Fonction de récupération des infos dans le fichier du graphe
void Graphe::load(string nomfile)
{
    string ligne;
    Sommet s;//Sommet
    int n,pos_x,pos_y;//numéro du sommet
    string nom;//Nom du sommet
    float sante, coef;//Poids et coefficient multiplicateur du sommet

    //ifstream file("graphe_1.txt", ios::in);//ouvre le fichier en mode lecture
    ifstream file(nomfile, ios::in);//ouvre le fichier en mode lecture

    if(file)//si ouverture réussie
    {
        file >> m_ordre;
        AllocOrdre(m_ordre);


        ///1ère partie du fichier : la liste de sommets et leurs attributs
        for(int k=0 ; k<m_ordre ; k++)
        {
            file >> n;
            s.setNum(n);//Numéro du sommet en premier
            file >> nom;
            s.setNom(nom);//Nom du sommet ensuite
            file >> sante;
            s.setSante(sante);//Santé du sommet
            file >> coef;
            s.setCoeff(coef);//Coef multiplicateur du sommet
            file >> pos_x;
            s.setPos_x(pos_x);
            file >> pos_y;
            s.setPos_y(pos_y);
            m_Sommets.push_back(s);//On ajoute le sommet au vecteur de sommets
        }


        ///2e partie du fichier : matrice d'ajdacences pondérée
        //Boucle de remplissage
        for(int i = 0 ; i < m_ordre ; i++)
        {
            for (int j = 0 ; j < m_ordre ; j ++)
            {
                file >> m_adjacences[i][j];
            }
        }

        file.close(); //Fermeture du fichier

    }
    else
    {
        cerr << "Erreur lors de l'ouveture du fichier";
    }

}

//Fonction d'affichage du graphe (test)
void Graphe::afficheInfos()
{
    cout << "Infos des sommets :"<< endl;
    for(int i =0; i < m_ordre ; i++)
    {
        cout << "Le sommet numero " << m_Sommets[i].getNum() << " correspond a " << m_Sommets[i].getNom() << " avec " << m_Sommets[i].getSante() << " de sante et de coef " << m_Sommets[i].getCoeff()<<endl;

        if(m_Sommets[i].getActif()==false)
        {
            cout << "Le sommet " << m_Sommets[i].getNum() << " est donc inactif." << endl;
        }
    }
    cout << endl;

    cout << "Matrice d'adjacence"<< endl;
    for(int i =0 ; i < m_ordre ; i++)
    {
        cout << endl;
        for(int j = 0 ; j < m_ordre ; j++)
        {
            cout << m_adjacences[i][j]<< " ";
        }
    }
}

void Graphe::save(string nomfile)
{
    ofstream file(nomfile, ios::trunc);

    if(file)
    {
        file<< m_ordre << endl;

        for(int i=0 ; i<m_ordre ; i++)
        {
            file << m_Sommets[i].getNum() << " " << m_Sommets[i].getNom() << " " << m_Sommets[i].getSante() << " " << m_Sommets[i].getCoeff() << " " << m_Sommets[i].getPos_x() << " " << m_Sommets[i].getPos_y() << endl;
        }

        for(int j=0 ; j < m_ordre ; j++)
        {
            for(int k=0 ; k < m_ordre ; k++)
            {
                file << m_adjacences[j][k] << " ";
            }
            file << endl;
        }

        file.close();
        allegro_message("sauvegarde");
    }
    else
    {
        cerr << "Erreur d'ouverture du fichier"<<endl;
    }
}

vector<vector<float> > Graphe::getTranspose()
{
    for (int i=0 ; i<m_ordre ; i++)
    {
        for (int j=0 ; j<m_ordre ; j++)
        {
            m_adjacences[i][j]=m_adjacences[j][i];
        }
    }
    return m_adjacences;
}

//Détermine les adjacences depuis la matrice d'adjacence
void Graphe::getAdjacents()
{
    for(int i=0 ; i < m_ordre; i++)
    {
        for(int j=0 ; j < m_ordre ; j++)
        {
            if(m_adjacences[i][j] !=0)
            {
                m_Sommets[i].est_adj_a(m_Sommets[j]);
            }
        }
    }
}

void Graphe::dfs(int n)
{
    getAdjacents();//Détermine toutes les adjacences dans le graphe

    for(int i=0 ; i<m_ordre ; i++)
    {
        if(m_Sommets[i].getNum()== n)//On prend le sommet correspondant au numéro mis en paramètre
        {
            m_Sommets[i].setMarque(true);//On marque le 1er sommet (celui en paramètre)
            for(int j=0 ; j<m_ordre ; j++)
            {
                if((m_Sommets[i].est_adj_a(m_Sommets[j])==true) && (m_Sommets[j].getMarque()==false))//Si le sommet est adjacent et n'est pas marqué
                {
                    cout << "Sommet marque : " << m_Sommets[j].getNum() <<endl; //affichage
                    dfs(m_Sommets[j].getNum());
                }
            }
        }
    }
}
vector<Sommet>Graphe::dfsbis(int n) // DFS qui retourne un vecteur avec tous les sommets marque
{
    vector<Sommet>temp;
    getAdjacents();//Détermine toutes les adjacences dans le graphe

    for(int i=0 ; i<m_ordre ; i++)
    {
        if(m_Sommets[i].getNum()== n)//On prend le sommet correspondant au numéro mis en paramètre
        {
            m_Sommets[i].setMarque(true);//On marque le 1er sommet (celui en paramètre)
            for(int j=0 ; j<m_ordre ; j++)
            {
                if((m_Sommets[i].est_adj_a(m_Sommets[j])==true) && (m_Sommets[j].getMarque()==false))//Si le sommet est adjacent et n'est pas marqué
                {

                    cout << "Sommet marque : " << m_Sommets[j].getNum() <<endl; //affichage
                    dfs(m_Sommets[j].getNum());
                    temp.push_back(m_Sommets[j]);
                }
            }
        }
        return temp;
    }


}
void Graphe::fillOrder(int i, stack<int> &Stack)
{
    // Mark the current node as visited and print it
    m_Sommets[i].setMarque(true);

    // Recur for all the vertices adjacent to this vertex
    for (int i=0 ; i<m_ordre ; i++)
    {
        for (int j=0 ; j<m_ordre ; j++)
        {
            if((m_Sommets[i].est_adj_a(m_Sommets[j])==true) && (m_Sommets[j].getMarque()==false))
            {
                fillOrder(j, Stack);
            }
        }
    }

    Stack.push(i);


}
void Graphe::Kosaraju()
{
    stack<int> Stack;

    // Mark all the vertices as not visited (For first DFS)
    //bool *visited = new bool[V];
    for(int i = 0; i < m_ordre; i++)
    {
        m_Sommets[i].setMarque(false);


    }

    // Fill vertices in stack according to their finishing times

    for(int i = 0; i < m_ordre; i++)
    {

        if(m_Sommets[i].getMarque()==false)
        {
            fillOrder(i, Stack);
        }


    }

    // Create a reversed graph
    Graphe g(getTranspose());

    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < m_ordre; i++)
    {
        m_Sommets[i].setMarque(false);


    }

    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();
        // Print Strongly connected component of the popped vertex
        if (m_Sommets[v].getMarque() == false)
        {
            g.dfs(v);
            cout << endl ;
        }
    }
}

void Graphe::add(BITMAP*page, int DernierSommet)
{
    mouse_x=SCREEN_W/2;
    mouse_y=SCREEN_H/2;
    int i = DernierSommet+1;

if(m_Sommets[i].getSante()!=0)
    {
        m_Sommets[i].affiche(page);
    }

else
    {
        cout << "Le sommet "<< i << " est inactif ! "<< endl;
    }
}

void Graphe::affiche_graphe(std::string nomfile)
{

    ///declaration
    int var_quit_affiche=0;
    int DernierSommet = 0;//Variable correspondant au numéro du dernier sommet affiché : 0 est toujours le 1er sommet affiché

    ///allegro
    BITMAP *page;
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    while(var_quit_affiche!=1)
    {
        clear_bitmap(page);

        //Test si le sommet n'a pas de santé nulle

        if(m_Sommets[0].getSante()!=0)//On affiche uniquement le 1er sommet : les autres seront ajoutés par l'utilisateur via la fonction add codée plus haut
        {
            m_Sommets[0].affiche(page);
        }


  for(int i=0 ; i< m_ordre ; i++)
        {
            ///Fonction pour déplacer les sommets avec la souris
            if(mouse_b &1 && mouse_x>m_Sommets[i].getPos_x()-38 && mouse_x<m_Sommets[i].getPos_x()+38 && mouse_y>m_Sommets[i].getPos_y()-38 && mouse_y<m_Sommets[i].getPos_y()+38)
            {
                while(mouse_b &1)
                {
                    m_Sommets[i].setPos_x(mouse_x);
                    m_Sommets[i].setPos_y(mouse_y);
                }
            }


            ///affichage des aretes
            for(int j=0 ; j < m_ordre ; j++)
            {
                //tracer l'arete que si sa "santé" est > 0
                if(m_adjacences[i][j] !=0 && m_Sommets[i].getActif()==true && m_Sommets[j].getActif()==true)
                {
                    line(page,m_Sommets[i].getPos_x(),m_Sommets[i].getPos_y(),m_Sommets[j].getPos_x(),m_Sommets[j].getPos_y(), makecol(50,100,255));
                }
            }
        }
    }


    ///barre d'outils
    //formes
    rectfill(page,0,0,100,768,makecol(255,255,255));//fond
    line(page,0,338,100,338,makecol(0,0,0));//ligne de separation centrale

    //textes des boutons
    textprintf_centre_ex(page,font,50,373,makecol(0,0,0),-1,"Save");//save
    textprintf_centre_ex(page,font,50,433,makecol(0,0,0),-1,"K-connex");//k connex
    textprintf_centre_ex(page,font,50,493,makecol(0,0,0),-1,"F-Connex");//forte connex
    textprintf_centre_ex(page,font,50,553,makecol(0,0,0),-1,"Add");//ajouter
    textprintf_centre_ex(page,font,50,613,makecol(0,0,0),-1,"Suppr");//supprimer
    textprintf_centre_ex(page,font,50,673,makecol(0,0,0),-1,"Retour");//retour
    textprintf_centre_ex(page,font,50,733,makecol(0,0,0),-1,"Quit");//quitter

    //hitbox des boutons
    rect(page,5,348,95,398,makecol(0,0,0));//save
    rect(page,5,408,95,458,makecol(0,0,0));//k connex
    rect(page,5,468,95,518,makecol(0,0,0));//forte connex
    rect(page,5,528,95,578,makecol(0,0,0));//ajouter
    rect(page,5,588,95,638,makecol(0,0,0));//supprimer
    rect(page,5,648,95,698,makecol(0,0,0));//av dernier cadre : retour
    rect(page,5,708,95,758,makecol(0,0,0));//cadre tout en bas : quitter

    //Actions

    //save
    if(mouse_x>5 && mouse_x<95 && mouse_y>348 && mouse_y<398)
    {
        if(mouse_b &1)
        {
            mouse_x=SCREEN_W/2;
            mouse_y=SCREEN_H/2;
            save(nomfile);
        }
    }

    //k connex
    if(mouse_x>5 && mouse_x<95 && mouse_y>408 && mouse_y<458)
    {
        if(mouse_b &1)
        {
            //fonction corresp
        }
    }

    //f connex
    if(mouse_x>5 && mouse_x<95 && mouse_y>468 && mouse_y<518)
    {
        if(mouse_b &1)
        {
            //fonction corresp
        }
    }

    //add
    if(mouse_x>5 && mouse_x<95 && mouse_y>528 && mouse_y<578)
    {
        if(mouse_b &1)
        {
            add(page, DernierSommet);
            DernierSommet++;
        }
    }

    //suppr
    if(mouse_x>5 && mouse_x<95 && mouse_y>588 && mouse_y<638)
    {
        if(mouse_b &1)
        {
            destroy();
        }
    }

    //retour
    if(mouse_x>5 && mouse_x<95 && mouse_y>648 && mouse_y<698)
    {
        if(mouse_b &1)
        {
            var_quit_affiche=1;
        }
    }

    //quitter
    if(mouse_x>5 && mouse_x<95 && mouse_y>708 && mouse_y<758)
    {
        if(mouse_b &1)
        {
            //allegro_exit();
            exit(-1);
        }
    }


    //reaffiche la souris par dessus
    show_mouse(page);
    blit(page,screen,0,0,0,0,1024,768);

}

int Graphe::kuplet(int k, int n)
{
    vector<float>t;
    t[0]=1;
    for (int i=0 ; i<=k ; i++ )
    {
        t[i]=1;
        for (int j=i-1 ; j>=1 ; j--)
        {
            t[j]=t[j]+t[j-1];

        }
    }
    return t[n];

}


void Graphe::kconnexite()
{
    int kmin=0;
    for (int k=0 ; k<m_ordre ; k++)
    {
        while (kmin=0)
        {
            for(int i =0 ; i<kuplet(k,m_ordre) ; i++)
            {

                if (dfsbis(k-m_ordre)[i].getNum()!=m_Sommets[i].getNum())
                {
                    kmin=k;
                }
            }
        }
    }
    cout<<"kmin="<<kmin<<endl;
}
