#include <iostream>
#include "Graphe.h"

using namespace std;

int main()
{
    Graphe graphe;
    string nomfile = "graphe_1.txt";
    graphe.load(nomfile);
    graphe.afficheInfos();
   /* graphe.destroy(1);
    graphe.destroy(0);
    graphe.destroy(2);
    graphe.afficheInfos();
    //graphe.save(nomfile);*/
    return 0;
}
