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
void Graphe::destroy(int n)
{
    for(int i=0 ; i<m_ordre ; i++)
    {
        if(m_Sommets[i].getNum()== n)
        {
            m_Sommets[i].setSante(0);
            m_Sommets[i].setActif(false);
        }
    }

    cout << "Destruction du sommet "<< n << " !"<< endl << endl;
}

//Fonction de récupération des infos dans le fichier du graphe
void Graphe::load(string nomfile)
{
    string ligne;
    Sommet s;//Sommet
    int n;//numéro du sommet
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
                    if(s.getSante()!=0)
                    {
                        s.setActif(true);
                    }
                    file >> coef;
                    s.setCoeff(coef);//Coef multiplicateur du sommet
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

//Fonction d'affichage du graphe
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
            file << m_Sommets[i].getNum() << " " << m_Sommets[i].getNom() << " " << m_Sommets[i].getSante() << " " << m_Sommets[i].getCoeff() << endl;
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

void Graphe::fillOrder(int i , stack<int> &Stack)
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
                fillOrder(j , Stack);
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
                fillOrder(i , Stack);
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


void Graphe::affiche_graphe()
{
    ///declaration
    int var_quit_affiche=0;

    ///allegro
    BITMAP *page;
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);
    show_mouse(page);

    while(var_quit_affiche!=1)
    {
        for(int i=0;i<m_ordre;i++)
        {
            circlefill(page,40,40,40,makecol(250,250,255));
            //m_Sommets[i].
        }
        blit(page,screen,0,0,0,0,1024,768);
    }
}








