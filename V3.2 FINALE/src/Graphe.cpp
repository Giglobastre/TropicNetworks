#include "Graphe.h"
#include <stack>


using namespace std;

Graphe::Graphe()
{
    m_ordre = 0;
    m_nbAretes = 0;
    m_nom = "";
    m_pause = false;

}
Graphe::Graphe(vector<vector<float> > adj)
{
    m_adjacences=adj;
}
Graphe::~Graphe()
{
}

///GETTERS

bool Graphe::getPause()
{
    return m_pause;
}

///SETTERS

void Graphe::setPause(bool val)
{
    m_pause = val;
}

///METHODES
void Graphe::AllocOrdre(int m_ordre)
{
    for(int i=0 ; i < m_ordre ; i ++)
    {
        m_adjacences.push_back(vector<float>(m_ordre));
    }
}

void Graphe::destroy()
{
    while(!mouse_b & 1)
    {
        for(int i =0 ; i < m_ordre ; i++)
        {
            if(mouse_b &1 && mouse_x>m_Sommets[i].getPos_x()-38 && mouse_x<m_Sommets[i].getPos_x()+38 && mouse_y>m_Sommets[i].getPos_y()-38 && mouse_y<m_Sommets[i].getPos_y()+38)
            {
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
vector<Sommet>Graphe::dfsbis(int n) // DFS qui retourne un vecteur avec tous les sommets marqués
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
void Graphe::remplissage(int i, stack<int> &Stack)
{
    //marque le sommet actuel
    m_Sommets[i].setMarque(true);

    //recommence pour toutes les aretes de ce noeud
    for (int i=0 ; i<m_ordre ; i++)
    {
        for (int j=0 ; j<m_ordre ; j++)
        {
            if((m_Sommets[i].est_adj_a(m_Sommets[j])==true) && (m_Sommets[j].getMarque()==false))
            {
                remplissage(j, Stack);
            }
        }
    }

    Stack.push(i);
}

void Graphe::Kosaraju()
{
    stack<int> Stack;

    // marque tout les sommets qui n'ont pas été visités
    for(int i = 0; i < m_ordre; i++)
    {
        m_Sommets[i].setMarque(false);


    }
    //les met dans le stack

    for(int i = 0; i < m_ordre; i++)
    {

        if(m_Sommets[i].getMarque()==false)
        {
            remplissage(i, Stack);
        }
        cout<<"forte connexite : "<<m_Sommets[i].getNom()<< endl ;
    }

    //creation de la matrice transposée
    Graphe g(getTranspose());

    //marque les sommets comme non visités pour une deuxime dfs
    for(int i = 0; i < m_ordre; i++)
    {
        m_Sommets[i].setMarque(false);


    }
    //analyse par l'ordre ou elle sont rentrées dans le stack
    while (Stack.empty() == false)
    {
        // pop un sommet du stack
        int v = Stack.top();
        Stack.pop();
        // affiche les sommets fortement connexes
        if (m_Sommets[v].getMarque() == false)
        {
            g.dfs(v);
            cout << endl ;
        }
    }
}

//fonction d'ajout de sommets
void Graphe::add(int DernierSommet)
{
    mouse_x=SCREEN_W/2;
    mouse_y=SCREEN_H/2;

    m_Sommets[DernierSommet].setActif(true);

}

//Fonction de suppression de sommets
void Graphe::supp(int DernierSommetsup)
{
    mouse_x=SCREEN_W/2;
    mouse_y=SCREEN_H/2;

    m_Sommets[DernierSommetsup].setActif(false);
}

void Graphe::affiche_graphe(std::string nomfile)
{

    ///declaration
    int var_quit_affiche=0;
    int var=-1;
    int DernierSommet=0;
    int DernierSommetsup=m_ordre;
    int nextTick= 0;

    ///allegro
    BITMAP *page;
    BITMAP *bouton;
    page=create_bitmap(SCREEN_W-100,SCREEN_H);
    bouton = create_bitmap(100, SCREEN_H);//bitmap d'affichage de la barre d'outils
    clear_bitmap(page);
    clear_bitmap(bouton);

    int debutBoucle = clock()*1000/CLOCKS_PER_SEC;

    affiche_boutons(bouton);

    while(var_quit_affiche!=1)
    {
        clear_bitmap(page);

        //boucle de parocurs de l'entieretée des sommets
        for(int i=0; i<m_ordre; i++)
        {
            //affichage des sommets
            if(m_Sommets[i].getActif()==true)
            {
                m_Sommets[i].affiche(page);
            }


            ///deplacement
            if(mouse_b &1 && mouse_x > m_Sommets[i].getPos_x()-30 && mouse_y > m_Sommets[i].getPos_y()-10 && mouse_x <m_Sommets[i].getPos_x()+30 && mouse_y<m_Sommets[i].getPos_y()+10 )
            {
                while(mouse_b&1)
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

            ///Actions
            // a chaque clic sur un bouton le curseur est envoyé ailleurs sur l'ecran pour pas qe plusieurs clics soient effectués

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
                    mouse_x=500;
                    mouse_y=500;
                    kconnexite();
                }
            }

            //f connex
            if(mouse_x>5 && mouse_x<95 && mouse_y>468 && mouse_y<518)
            {
                if(mouse_b &1)
                {
                    mouse_x=500;
                    mouse_y=500;
                    Kosaraju();
                }
            }

            //add
            if(mouse_x>5 && mouse_x<95 && mouse_y>528 && mouse_y<578)
            {
                if(mouse_b &1)
                {
                    add(DernierSommet);
                    DernierSommet++;
                }
            }

            //suppr
            if(mouse_b &1 && mouse_x>5 && mouse_x<95 && mouse_y>588 && mouse_y<638)
            {


                supp(DernierSommetsup);
                DernierSommetsup--;
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
                    exit(-1);
                }
            }

            //modif sante
            if(mouse_x>5 && mouse_x<95 && mouse_y>168 && mouse_y<218)
            {
                if(mouse_b &1)
                {
                    string nomSommet;
                    int sante;
                    cout << "De quel sommet souhaitez-vous modifier la sante ?"<<endl;
                    cin >> nomSommet;
                    for(int i=0 ; i<m_ordre ; i++)
                        {
                            if(m_Sommets[i].getNom()== nomSommet)//On prend le sommet correspondant au numéro mis en paramètre
                            {
                                cout << "Saisir la nouvelle sante : ";
                                cin >> sante;
                                m_Sommets[i].setSante(sante);
                                cout << endl << "Nouvelle sante de "<< m_Sommets[i].getNom() <<" : " << m_Sommets[i].getSante()<<endl;
                            }
                        }
                }
            }

            //modif coeff
            if(mouse_x>5 && mouse_x<95 && mouse_y>228 && mouse_y<278)
            {
                if(mouse_b &1)
                {
                    string nomSommet;
                    float coef;
                    cout << "De quel sommet souhaitez-vous modifier le coefficient ?"<<endl;
                    cin >> nomSommet;
                    for(int i=0 ; i<m_ordre ; i++)
                        {
                            if(m_Sommets[i].getNom()== nomSommet)//On prend le sommet correspondant au numéro mis en paramètre
                            {
                                cout << "Saisir le nouveau coef. : ";
                                cin >> coef;
                                m_Sommets[i].setCoeff(coef);
                                cout << endl << "Nouveau coef de "<< m_Sommets[i].getNom() <<" : " << m_Sommets[i].getCoeff()<<endl;
                            }
                        }
                }
            }

            //pause
            if(mouse_x>5 && mouse_x<95 && mouse_y>288 && mouse_y<338)
            {
                if(mouse_b &1)
                {
                    pause();
                }
            }
        }

        //reaffiche la souris par dessus
        show_mouse(page);
        if(mouse_x < 100)
        {
            show_mouse(bouton);
        }
        blit(page,screen,0,0,100,0,1024,768);
        blit(bouton,screen,0,0,0,0,100,768);

    int timer = clock() *1000/CLOCKS_PER_SEC;

        //Timer toutes les 1s
        if((timer-debutBoucle)/1000 == nextTick)
        {
            croissance();
            nextTick++;
        }
    }
}

///combinaison des k parmis n
//algorithme trouvé sur commentcamarche
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
    // pour i allant de 0 au k-uplet
    for (int k=0 ; k<m_ordre ; k++)
    {
        while (kmin=0)
        {
            for(int i =0 ; i<kuplet(k,m_ordre) ; i++)
            {
                //si tous les sommets présent dans le conteneur du DFS du graphe avec en elevant le k-ème sommet
                //correspondent a tous les sommets du graphe alors c'est le k de l'algorithme
                if (dfsbis(k-m_ordre)[i].getNum()!=m_Sommets[i].getNum())
                {
                    kmin=k;
                }
            }
        }
    }
    cout<<"kmin="<<kmin<<endl;
}



void Graphe::croissance()
{
    if(getPause()==false)//Si le système n'est pas en pause
        {
            for(int i=0; i < m_ordre ; i++)
            {
                for(int j=0 ; j < m_ordre ; j++)
                {
                    if(m_adjacences[i][j]!=0)
                        {
                            m_Sommets[i].setSante( m_Sommets[i].getSante() + ( (m_Sommets[i].getCoeff() * m_Sommets[i].getSante()) * (1 - (m_Sommets[i].getSante() / (m_adjacences[i][j] * m_Sommets[j].getSante() ) ) ) )  );
                        }
                    else
                    {
                        if(m_adjacences[j][i]!=0)
                        {
                            m_Sommets[i].setSante(m_Sommets[i].getSante() +  (m_Sommets[i].getCoeff() * m_Sommets[i].getSante()) -(m_adjacences[j][i] * m_Sommets[j].getSante()));
                        }
                    }
                }

            //Si le sommet a une santé négative on la met à 0 (impossible d'avoir un nombre négatif d'individu)
                if(m_Sommets[i].getSante()<0)
                    {
                        m_Sommets[i].setSante(0);
                    }


                cout << "Sante de " << m_Sommets[i].getNom() << " : " << m_Sommets[i].getSante()<<endl;
            }
            cout <<endl;
        }

        else
        {
            cout <<endl << "Systeme en pause"<<endl;
        }
}


//Fonction permettant de pauser/relancer la fonction de croissance

void Graphe::pause()
{
    if(getPause() == true)
    {
        setPause(false);
    }

    if(getPause() == false)
    {
        setPause(true);
    }
}

void Graphe::affiche_boutons(BITMAP * page)
{

            ///barre d'outils
            //formes
            rectfill(page,0,0,100,768,makecol(255,255,255));//fond
            //line(page,0,338,100,338,makecol(0,0,0));//ligne de separation centrale

            //textes des boutons
            textprintf_centre_ex(page,font,50,193,makecol(0,0,0),-1,"mod. sante");//modif santz
            textprintf_centre_ex(page,font,50,253,makecol(0,0,0),-1,"mod. coeff");//modif coeff
            textprintf_centre_ex(page,font,50,313,makecol(0,0,0),-1,"pause");//pause
            textprintf_centre_ex(page,font,50,373,makecol(0,0,0),-1,"Save");//save
            textprintf_centre_ex(page,font,50,433,makecol(0,0,0),-1,"K-connex");//k connex
            textprintf_centre_ex(page,font,50,493,makecol(0,0,0),-1,"F-Connex");//forte connex
            textprintf_centre_ex(page,font,50,553,makecol(0,0,0),-1,"Add");//ajouter
            textprintf_centre_ex(page,font,50,613,makecol(0,0,0),-1,"Suppr");//supprimer
            textprintf_centre_ex(page,font,50,673,makecol(0,0,0),-1,"Retour");//retour
            textprintf_centre_ex(page,font,50,733,makecol(0,0,0),-1,"Quit");//quitter

            //hitbox des boutons
            rect(page,5,168,95,218,makecol(0,0,0));//modif sante
            rect(page,5,228,95,278,makecol(0,0,0));//modif coeff
            rect(page,5,288,95,338,makecol(0,0,0));//pause
            rect(page,5,348,95,398,makecol(0,0,0));//save
            rect(page,5,408,95,458,makecol(0,0,0));//k connex
            rect(page,5,468,95,518,makecol(0,0,0));//forte connex
            rect(page,5,528,95,578,makecol(0,0,0));//ajouter
            rect(page,5,588,95,638,makecol(0,0,0));//supprimer
            rect(page,5,648,95,698,makecol(0,0,0));//av dernier cadre : retour
            rect(page,5,708,95,758,makecol(0,0,0));//cadre tout en bas : quitter

}
