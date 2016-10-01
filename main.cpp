#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Partie.h"
#include "Interface.h"

/*-------------------variables globales----------------------*/

int j=1, vide, continuer, encours;      // j : colonne dans laquelle on joue, vide : ligne vide pour une colonne donnée, continuer : la partie est en cours, encours : le jeu est en cours
int level=6;                            // level est la profondeur de l'IA pour l'algorithme NegaMax

int main(int argc, char *argv[]){

    Interface e (2);
    Partie partie(0,0,0,0,0,false);
    partie.raz();

    SDL_Init(SDL_INIT_VIDEO);           // initialisation SDL
    TTF_Init();                         // initialisation SDL_ttf (affichage du texte)

    int menu = 1;                       // menu = 1 : on est sur la page menu
    encours = 1;                        // encours = 1 : le jeu est en cours

    e.initialisationSDL();
    e.pageDeDemarrage();
    e.choixMenu(menu);

    while (encours) {                   // tant que le joueur veut jouer

        int choix = 1;                  // choix = 1 : on est sur la page de choix du niveau
        continuer = 1;                  // continuer = 1 : la partie est en cours
        e.choixNiveau(choix);
        if (encours == 1) {                         // si le joueur n'a pas quitté depuis l'écran de bienvenue
            partie.raz();
            e.reinitialisationGrille();
            e.choixColonne(continuer, partie);
        }
    }

    e.~Interface();                     // destructeur de la classe Interface
    partie.~Partie();                   // destructeur de la classe Partie

    TTF_Quit();                         // on quitte SDL_ttf
    SDL_Quit();                         //on quitte SDL

    return EXIT_SUCCESS;
}
