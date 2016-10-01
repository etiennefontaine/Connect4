#ifndef Interface_h
#define Interface_h

#include <SDL.h>
#include <SDL_ttf.h>
#include "Partie.h"

class Interface{

    public :

       SDL_Surface *ecran;                                              // c'est la fenêtre de jeu
	   SDL_Surface *texte;                                              // c'est le texte qui sera affiché
	   SDL_Surface *Grille;                                             // grille du jeu
	   SDL_Surface *pionrouge;                                          // pions du joueur
	   SDL_Surface *pionjaune;                                          // pions de l'ordinateur
	   SDL_Surface *haut;                                               // zone en haut de la fenêtre de jeu
	   SDL_Surface *bas;                                                // zone en bas

	   SDL_Rect position;                                               // coordonnées
	   SDL_Rect positionJouable;

	   TTF_Font *police;
	   SDL_Color couleurTexte;
	   SDL_Event event;

    Interface(int p=0);
    ~Interface();

	void initialisationSDL();
	void afficherDuTexte(const char *chaine,int a,int b,int c);
	void pageDeDemarrage();
	void choixMenu(int menu);
	void choixNiveau(int choix);
	void choixColonne(int continuer,Partie & partie);
	void reinitialisationGrille();
	void reinitialisationPosition();
	void jouer(int continuer,Partie&  partie);
	void jouerUnCoupJoueur(Partie & partie );
	void jouerUnCoupOrdi(Partie & partie );
	void jeuFini(int continuer,const char *chaine,Partie & partie);

};
#endif
