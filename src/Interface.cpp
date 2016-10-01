#include "Interface.h"

extern int j, vide, continuer, encours;
extern int level;

Interface :: Interface(int p){

    ecran=SDL_SetVideoMode(800, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );       //c'est la fenêtre de dimension 800*70
    haut = SDL_CreateRGBSurface(SDL_HWSURFACE, 800, 50, 32, 0, 0, 0, 0);        //zone en haut de la fenêtre
    bas = SDL_CreateRGBSurface(SDL_HWSURFACE, 800, 100, 32, 0, 0, 0, 0);        //idem mais en bas
    Grille = SDL_LoadBMP("grille.bmp");                                         //grille de jeu
    pionrouge = SDL_LoadBMP("pionrouge.bmp");                                   //pions du joueur
    pionjaune = SDL_LoadBMP("pionjaune.bmp");                                   //pions de l'ordinateur

    position={p};
    positionJouable={p};

    police = NULL;
    texte = NULL;
    couleurTexte = {255, 255, 255};                                             //couleur blanche pour le texte
    event.type=0;

    SDL_WM_SetCaption("Jeu de Puissance 4", NULL);                              // titre de la fenêtre
    SDL_WM_SetIcon(SDL_LoadBMP("icone.bmp"), NULL);                             // icone de la fenêtre
}

/*--------------------destructeur de Interface--------------------*/

Interface :: ~Interface(){
        SDL_FreeSurface(ecran);
        SDL_FreeSurface(texte);
        SDL_FreeSurface(pionrouge);
        SDL_FreeSurface(pionjaune);
        SDL_FreeSurface(Grille);
        SDL_FreeSurface(haut);
        SDL_FreeSurface(bas);
        TTF_CloseFont(police);
}

/*-------------------initialisation des différents outils de la sdl----------------------*/

void Interface :: initialisationSDL(){

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));                                 //on met un écran noir pour la fenêtre
        SDL_SetColorKey(Grille, SDL_SRCCOLORKEY, SDL_MapRGB(Grille -> format, 255, 255, 255));
        SDL_SetColorKey(pionrouge, SDL_SRCCOLORKEY, SDL_MapRGB(pionrouge->format, 255, 255, 255));
        SDL_SetColorKey(pionjaune, SDL_SRCCOLORKEY, SDL_MapRGB(pionjaune->format, 255, 255, 255));

}

/*-------------------fonction pour afficher une phrase à l'écran----------------------*/

void Interface :: afficherDuTexte(const char *chaine,int a,int b,int c){

        police = TTF_OpenFont("times.ttf", a);                                  // choix de la police et de la taille du texte (a)
        texte = TTF_RenderText_Blended(police, chaine, couleurTexte);
        position.x = b;                                                         // coordonnées du début du texte
        position.y = c;                                                         // coordonnées du début du texte
        SDL_BlitSurface(texte, NULL, ecran, &position);                         // on "blitte" le texte : affichage de celui-ci
}

/*-------------------page d'accueil du jeu----------------------*/

void Interface :: pageDeDemarrage(){

        afficherDuTexte("Bienvenue dans ce jeu de Puissance 4 !",45,61,40);
        afficherDuTexte("Vous allez pouvoir jouer contre l'ordinateur.",35,91,190);
        afficherDuTexte("Vous aurez les pions rouges, lui les pions jaunes.",35,61,250);
        afficherDuTexte("Appuyer sur la touche 'Entrée' pour jouer.",35,101,310);
        afficherDuTexte("En cours de partie, appuyer sur la touche 'Echap'.",35,61,370);
        afficherDuTexte("ou cliquez sur la croix rouge pour quitter le jeu.",35,71,430);
        afficherDuTexte("Bonne chance !",50,221,540);
        SDL_Flip(ecran);                                        // actualisation de l'écran pour affichage du texte sur fond noir
}

/*-------------------l'utilisateur choisit de faire une partie ou de quitter----------------------*/

void Interface :: choixMenu(int menu){

        while (menu){                                       // tant qu'on est dans le menu (affichage des instructions)
            SDL_WaitEvent(&event);
            switch(event.type){
                case SDL_QUIT:                              // si clic sur quitter alors fermer la fenêtre
                    menu = 0;
                    encours = 0;
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym){
                    case SDLK_RETURN:                       //si clic sur entrée passer à l'écran suivant
                    menu = 0;
                    break;
                    case SDLK_ESCAPE:                       // si clic sur échap alors quitter
                        menu = 0;
                        encours = 0;
                    break;
                default:
                    ;
                    };
            break;
            }
        }
}

/*-------------------l'utilisateur choisit le niveau de difficulté parmi 3 possibilités----------------------*/

void Interface :: choixNiveau(int choix){

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
    afficherDuTexte("Vous pouvez jouer à trois niveaux différents :",35,91,220);
    afficherDuTexte("Appuyer sur 1 pour jouer en niveau facile",35,101,280);
    afficherDuTexte("Appuyer sur 2 pour jouer en niveau moyen",35,96,340);
    afficherDuTexte("Appuyer sur 3 pour jouer en niveau difficile",35,91,400);
    SDL_Flip(ecran);

    while (choix){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                choix = 0;
                continuer = 0;
                encours = 0;
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        choix = 0;
                        continuer = 0;
                        encours = 0;
                        break;
                    case SDLK_KP1:                  //le joueur choisit le niveau 1
                        level=5;                    //profondeur de l'algorithme : 5
                        choix = 0;
                        break;
                    case SDLK_KP2:                  // niveau 2
                        level=6;                    // profondeur de 6
                        choix = 0;
                        break;
                    case SDLK_KP3:                  // niveau 3
                        level=7;                    // profondeur de 7
                        choix = 0;
                        break;
                    default:
                        break;
                };
        break;
        }
    }
}

/*-------------------l'utilisateur choisit la colonne dans laquelle il va jouer----------------------*/

void Interface :: choixColonne(int continuer,Partie & partie){
    partie.setFin(false);
    while(continuer){                                       // tant que la partie continue

    reinitialisationPosition();
    SDL_WaitEvent(&event);                                  // on attend l'évènement SDL
    switch(event.type){
        case SDL_QUIT:                                      // si le joueur quitte, arrêter le jeu
            continuer = 0;
            encours = 0;
            partie.setFin(true);
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym){
            case SDLK_ESCAPE:                               // idem pour la touche echap
                continuer = 0;
                encours = 0;
                partie.setFin(true);
                break;
            case SDLK_RETURN:                               //si le joueur appuie sur entrée, recommencer la partie
                continuer=0;
                partie.setFin(true);
                break;
            case SDLK_KP1:                                  // le joueur joue en colonne 1
                if (!partie.getFin()){                      // si le jeu n'est pas terminé
                j=0;
                jouer(continuer,partie);                    // jouer en colonne 1
                }
                break;
            case SDLK_KP2:
                if (!partie.getFin()){
                j=1;
                jouer(continuer, partie);
                }
                break;
            case SDLK_KP3:
                if (!partie.getFin()){
                j=2;
                jouer(continuer,partie);
                }
                break;
            case SDLK_KP4:
                if (!partie.getFin()){
                j=3;
                jouer(continuer,partie);
                }
                break;
            case SDLK_KP5:
                if (!partie.getFin()){
                j=4;
                jouer(continuer,partie);
                }
                break;
            case SDLK_KP6:
                if (!partie.getFin()){
                j=5;
                jouer(continuer,partie);
                }
                break;
            case SDLK_KP7:
                if (!partie.getFin()) {
                j=6;
                jouer(continuer,partie);
                }
                break;
            default :
                break;
            };
        default :
            break;
        }

        if(partie.rempli() && partie.vainqueur()==10){               // si la grille est remplie sans vainqueur
                jeuFini(continuer,"Match nul !",partie);            // afficher match nul
                partie.addNul(1);                                   // un match nul de plus dans le compteur
            }
    }
}

/*-------------------grille au cours du jeu----------------------*/

void Interface :: reinitialisationGrille(){

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
        position.x = (800/2)-(674/2);
        position.y = (700/2)- (579/2);
        SDL_BlitSurface(Grille, NULL, ecran, &position);                            // affichage de la grille au milieu de la fenêtre
        afficherDuTexte("Entrez une colonne entre 1 et 7",55,61,635);
        afficherDuTexte("   1     2     3    4     5     6     7",55,61,0);
        positionJouable.y = 0;                                                      // initialisation de l'ordonnée de la position jouable
        SDL_Flip(ecran);
}

/*-------------------position réinitialisé à chaque coup----------------------*/

void  Interface :: reinitialisationPosition(){

        position.x = (800/2)-(674/2);
        position.y = (700/2)- (579/2);
        SDL_BlitSurface(Grille, NULL, ecran, &position);                            // on re-blitte la grille (juste pour l'esthétisme)
        SDL_Flip(ecran);
}

/*-------------------le joueur joue puis l'ordinateur----------------------*/

void Interface :: jouer(int continuer,Partie & partie){

        if(partie._p[0][j] ==10){                                                      //on peut jouer dans la colonne j
            jouerUnCoupJoueur(partie);                                                 //le joueur joue
            if(partie.vainqueur()==1)  {                                               //le joueur a gagné ?
                partie.addGain(1);
                partie.setFin(true);                                                   //une victoire de plus au compteur
                jeuFini(continuer,"Vous avez gagné !",partie);                         //fin de la partie
                return;
            }

            j=partie.IA();                                                             //colonne dans laquelle l'ordi joue
            jouerUnCoupOrdi(partie);                                                   //l'ordi joue
            if(partie.vainqueur()==0){                                                 //l'ordi a gagné ?
                partie.addPerte(1);                                                    //une défaite de plus au compteur
                partie.setFin(true);
                jeuFini(continuer,"Vous avez perdu !",partie);                          //fin de la partie
                return;
            }
        }
}

/*-------------------on place un pion rouge ou jaune selon la colonne choisie----------------------*/

void Interface :: jouerUnCoupJoueur(Partie & partie ){

        positionJouable.y = 1000;
        for (int i =0; i <=5; i++){                                 //on cherche où jouer dans la colonne j
            if (partie._p[i][j] ==10){
                positionJouable.y = 62+96*i;
                vide = i;
            }
        }
        partie._p[vide][j] = 1;                                     //on remplit la case du tableau où le coup est joué
        position.x = 64+96*j;                                       //coordonnées pour placer le pion
        position.y = positionJouable.y;                             //idem
        SDL_BlitSurface(pionrouge, NULL, ecran, &position);
        SDL_Flip(ecran);
}

/*-------------------on place un pion rouge ou jaune selon la colonne choisie----------------------*/

void Interface :: jouerUnCoupOrdi(Partie & partie ){

        positionJouable.y = 1000;
        for (int i =0; i <=5; i++){                                 //on cherche où jouer dans la colonne j
            if (partie._p[i][j] ==10){
                positionJouable.y = 62+96*i;
                vide = i;
            }
        }
        partie._p[vide][j] = 0;                                     //on remplit la case du tableau où le coup est joué
        position.x = 64+96*j;                                       //coordonnées pour placer le pion
        position.y = positionJouable.y;                             //idem
        SDL_BlitSurface(pionjaune, NULL, ecran, &position);
        SDL_Flip(ecran);
}

/*-------------------affichage de l'option rejouer en fin de partie----------------------*/

void Interface :: jeuFini(int continuer,const char *chaine,Partie & partie){

        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(haut, NULL, ecran, &position);                              //on affiche un rectangle noir (haut) pour masquer le texte
        position.y = 640;
        SDL_BlitSurface(bas, NULL, ecran, &position);                               //idem mais en bas
        afficherDuTexte(chaine,50,61,0);

        char nombreV[30] = "";                                                      // pour afficher le compteur de victoires
        sprintf(nombreV, "Nombre Victoires : %d",partie.getGain());
        afficherDuTexte(nombreV,20,550,0);

        char nombreD[30] = "";
        sprintf(nombreD, "Nombre Défaites : %d",partie.getPerte());
        afficherDuTexte(nombreD,20,550,20);

        char nombreN[30] = "";
        sprintf(nombreN, "Nombre Matchs Nuls : %d",partie.getNul());
        afficherDuTexte(nombreN,20,550,40);

        afficherDuTexte("Rejouer : 'Entrée' ---------- Quitter : 'Echap'",40,61,635);
        SDL_Flip(ecran);
        partie.setFin(true);                                                        //on passe le booléan à true pour ne plus pouvoir afficher de pion
}
