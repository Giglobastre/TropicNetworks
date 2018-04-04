#include <iostream>
#include <allegro.h>

int Quitter()
{
    return 1;
}

void Graphe(BITMAP *page)
{
    ///declarations
    int var_quit_selec=0;
    std::string nomfile;

    ///allegro
    clear_bitmap(page);
    show_mouse(page);

    ///boucle
    while(var_quit_selec!=1)
    {
        ///texte
        textprintf_centre_ex(page,font,1024/2,768/6,makecol(255,255,255),-1,"CHOIX DU GRAPHE");//titre
        textprintf_centre_ex(page,font,1024/2,768/3,makecol(255,255,255),-1,"Graphe 1");//graphe 1
        textprintf_centre_ex(page,font,1024/2,768/2,makecol(255,255,255),-1,"Graphe 2");//graphe 2
        textprintf_centre_ex(page,font,1024/2,768/1.5,makecol(255,255,255),-1,"Graphe 3");//Graphe 3
        textprintf_centre_ex(page,font,1024/2,700,makecol(255,255,255),-1,"Retour au menu");//Retour


        ///encadrement
        rect(page,412,120,612,140,makecol(255,255,255));//encadrement titre
        rect(page,412,246,612,266,makecol(255,255,255));//premier cadre
        rect(page,412,374,612,394,makecol(255,255,255));//deuxieme cadre
        rect(page,412,502,612,522,makecol(255,255,255));//troisieme cadre
        rect(page,412,690,612,710,makecol(255,255,255));//cadre retour

        ///hitbox sur clic
        if(mouse_b & 1)
        {

            //Premier cadre
            if(mouse_x>412 && mouse_x<612 && mouse_y>246 && mouse_y<266)
            {
                nomfile="graphe_1.txt";
                //add fonction avc bails de guigz pr les autres ossi
            }

            //Deuxieme cadre
            if(mouse_x>412 && mouse_x<612 && mouse_y>374 && mouse_y<394)
            {
                nomfile="graphe_2.txt";
            }

            //troisieme cadre
            if(mouse_x>412 && mouse_x<612 && mouse_y>502 && mouse_y<522)
            {
                nomfile="graphe_3.txt";
            }

            //cadre retour
            if(mouse_x>412 && mouse_x<612 && mouse_y>690 && mouse_y<710)
            {
                var_quit_selec=Quitter();
            }
        }
        blit(page,screen,0,0,0,0,1024,768);
    }
}


///voir popur utiliser "set_mouse_cursor" ou "set_mouse_cursor_bitmap" pour changer curseur
int main()
{
    /// declarations
    int var_quit_main=0;//variable servant a quitter le programme

    /// initialisation  allegro
    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();


    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    ///Bitmaps
    // BITMAP servant de buffer d'affichage
    BITMAP *page;

    // BITMAP devant recevoir l'image
    BITMAP *image;

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);


    ///Boucle
    while (var_quit_main!=1)
    {
        clear_bitmap(page);
        show_mouse(page);

        ///affichage menu texte
        textprintf_centre_ex(page,font,1024/2,768/6,makecol(0,255,122),-1,"TROPHIC NETWORKS");//titre => voir pour une autre police
        textprintf_centre_ex(page,font,1024/2,768/2,makecol(255,255,255),-1,"Choisir graph");//1er choix
        textprintf_centre_ex(page,font,1024/2,768/1.5,makecol(255,255,255),-1,"Quitter");//quitte le jeu si on le choisis

        ///affichage cadre et hitbox
        rect(page,412,120,612,140,makecol(0,255,0));//encadrement titre
        rect(page,412,374,612,394,makecol(255,255,255));//premier cadre
        rect(page,412,502,612,522,makecol(255,255,255));//deuxieme cadre

        ///si on clique dans l'une des hitbox effectue les actions correspondantes
        if(mouse_b & 1)
        {
            //Premier cadre
            if(mouse_x>412 && mouse_x<612 && mouse_y>374 && mouse_y<394)
            {
                Graphe(page);
            }

            //Deuxieme cadre
            if(mouse_x>412 && mouse_x<612 && mouse_y>502 && mouse_y<522)
            {
                var_quit_main=Quitter();
            }
        }

        //affichage final
        blit(page,screen,0,0,0,0,1024,768);
    }

    return 0;
}
END_OF_MAIN();
