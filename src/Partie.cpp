#include "Partie.h"

extern int level;

Partie :: Partie(int c,int v,int g,int p,int nombre,bool f){
        _compteur=c;
        _valeur = v;
        _gain=g;
        _perte=p;
        _nul=nombre;
        _fin=f;

        for(int i=0;i<=5;i++){                                  // on initialise chaque case du tableau � 10 (10 signifie que la case est vide)
            for(int j=0;j<=6;j++){
            _p[i][j]=10;
            }
        }
}

/*-------------------destructeur----------------------*/

Partie :: ~Partie(){
        for(int i=0;i<=5;i++) delete [] _p[i];               // on supprime le tableau
        delete [] _p;
}

/*-------------------constructeur copie----------------------*/

Partie::Partie(const Partie &source){

	_compteur = source._compteur;
	_valeur = source._valeur;
	_gain = source._gain;
	_perte = source._perte;
	_nul = source._nul;
	_fin = source._fin;

	for (int i = 0; i <= 5; i++){
		for (int j = 0; j <= 6; j++){
			_p[i][j] = source._p[i][j];
		}
	}
}
/*----------fonctions pour r�cup�rer la valeur de nos variables-----------*/

int Partie :: getCompteur(){                            // r�cup�ration de _compteur
    return _compteur;
}

int Partie :: getValeur(){                              // r�cup�ration de _valeur
    return _valeur;
}

int Partie :: getGain(){                                // r�cup�ration de _gain
    return _gain;
}

int Partie :: getPerte(){                               // r�cup�ration de _perte
    return _perte;
}

int Partie :: getNul(){                                 // r�cup�ration de _nul
    return _nul;
}

int Partie :: getFin(){                                 // r�cup�ration de _fin
    return _fin;
}

/*-------------------fonctions pour changer la valeur de nos variables----------------------*/

void Partie :: setCompteur(int c){                      // r�initialisation de _compteur
    _compteur=c;
}

void Partie :: setValeur(int v){                        // r�initialisation de _valeur
    _valeur=v;
}

void Partie :: setGain(int g){                          // r�initialisation de _gain
    _gain=g;
}

void Partie :: setPerte(int p){                         // r�initialisation de _perte
    _perte=p;
}

void Partie :: setNul(int nombre){                      // r�initialisation de _nul
    _nul=nombre;
}

void Partie :: setFin(bool f){                          // r�initialisation de _nul
    _fin=f;
}

/*-------------------fonctions d'addition----------------------*/

void Partie :: addCompteur(int c){                      // augmentation de _compteur
    _compteur+=c;
}

void Partie :: addValeur(int v){                        // augmentation de _valeur
    _valeur+=v;
}

void Partie :: addGain(int g){                          // augmentation de _gain
    _gain+=g;
}

void Partie :: addPerte(int p){                         // augmentation de _perte
    _perte+=p;
}

void Partie :: addNul(int nombre){                      // augmentation de _nul
    _nul+=nombre;
}

/*-------------------fonctions de soustraction----------------------*/

void Partie :: subCompteur(int c){                      // diminution de _compteur
    _compteur-=c;
}

void Partie :: subValeur(int v){                        // diminution de _valeur
    _valeur-=v;
}
/*-------------------on r�initialise le tableau pour faire une nouvelle partie----------------------*/

void Partie :: raz(){

    setCompteur(0);                                     // on remet toutes les variables � 0
    setValeur(0);

    for(int i=0;i<=5;i++){                              // on remet les cases du tableau � 10
        for(int j=0;j<=6;j++){
            _p[i][j]=10;
        }
    }
}

/*-------------------on renvoie l'indice i correspondant � la 1�re ligne vide de la colonne j----------------------*/

int Partie :: coupJouable(int j){

        int i=0;

        if(j<0 || j>6) return -1;                       // la colonne n'existe pas

        if(_p[i][j]!=10) return -1;                     // la colonne est remplie

        while(_p[i+1][j]==10 && i<=5){                  // la case est vide

            i++;
        }

        return i;
}

/*-------------------on regarde si le tableau est rempli----------------------*/

bool Partie :: rempli (){

    for(int i=0;i<=5;i++){                              // on parcourt le tableau
        for(int j=0;j<=6;j++){
            if(_p[i][j]==10) return false;              // il reste une case vide
        }
    }
    return true;
}

/*----------------------recherche d'un vainqueur de type n dans le jeu-----------------------*/

int Partie :: vainqueur (){

    /*---------recherche de 4 pions align�s en horizontal---------*/

        for(int i=0;i<=5;i++){
            for(int j=0;j<=3;j++){

                if(_p[i][j]==_p[i][j+1] && _p[i][j]==_p[i][j+2] && _p[i][j]==_p[i][j+3]) {

                    if(_p[i][j]!=10) return _p[i][j];
                }
            }
        }
    /*---------recherche de 4 pions align�s en vertical---------*/

        for(int j=0;j<=6;j++){
            for(int i=0;i<=2;i++){

            if(_p[i][j]==_p[i+1][j] && _p[i][j]==_p[i+2][j] && _p[i][j]==_p[i+3][j] ){

                    if(_p[i][j]!=10) return _p[i][j];
                }
            }
        }
    /*---------recherche de 4 pions align�s en diagonale Nord-Ouest / Sud-Est---------*/

        for(int i=0;i<=2;i++){
            for(int j=0;j<=3;j++){

                if(_p[i][j]==_p[i+1][j+1] && _p[i][j]==_p[i+2][j+2] && _p[i][j]==_p[i+3][j+3]) {

                    if(_p[i][j]!=10) return _p[i][j];
                }
            }
        }
    /*---------recherche de 4 pions align�s en diagonale Nord-Est / Sud-Ouest---------*/

        for(int i=5;i>=3;i--){
            for(int j=0;j<=3;j++){

                if(_p[i][j]==_p[i-1][j+1] && _p[i][j]==_p[i-2][j+2] && _p[i][j]==_p[i-3][j+3]) {

                    if(_p[i][j]!=10) return _p[i][j];
                }
            }
        }

        return 10;          //pas de gagnant
}

/*------------------------------impl�mentation de l'IA------------------------------*/

int Partie :: IA(){

        float tab[2] = {10000000 , 0 };

        for(int j = 0 ; j <= 6 ; j ++){                 //est-ce que l'ordi gagne au prochain coup ?
            int i = coupJouable(j);                     //r�cup�ration de la ligne o� on peut jouer en colone j
            if( i != -1 ){                              //on peut jouer dans la colonne
                _p[i][j] =0;                            //l'ordi joue
                if(vainqueur()==0){                     //l'ordi peut gagner au prochain coup
                   _p[i][j] =10;                        //on lib�re la case
                   return j ;							//on renvoie j car l'ordi est assur� de gagner
                }
              _p[i][j] =10;                             //on lib�re la case
            }
        }

        for(int j = 0 ; j <= 6 ; j ++){                 //est-ce que le joueur gagne au prochain coup ?
            int i = coupJouable(j);                     //r�cup�ration de la ligne o� on peut jouer en colone j
            if( i != -1 ){                              //on peut jouer dans la colonne
                _p[i][j] =1;                            //le joueur joue
                if(vainqueur()==1){                     //le joueur peut gagner au prochain coup
                   _p[i][j] =10;                        //on lib�re la case
                   return j ;							//on renvoie j car le joueur est assur� de gagner au coup suivant, on doit l'en emp�cher
                }
              _p[i][j] =10;                             //on lib�re la case
            }
        }

        for(int j = 0 ; j <= 6 ; j ++){                 //on fait jouer l'ordinateur successivement dans les 7 colonnes et on appelle la fonction algorithme

            setCompteur(0);                             //on r�initialise _compteur � 0
            setValeur(0);                               //on r�initialise _valeur � 0
            int i = coupJouable(j);                     //r�cup�ration de la ligne dans laquelle on peut jouer en colonne j

            if( i != -1 ){                              //on peut jouer en colonne j
                _p[i][j] =0;                            //l'ordi joue
                float inter = -(100*Algorithme(1));		//on r�cup�re la valeur de Algorithme
                if(_compteur != 0)  inter -= ((100*_valeur)/_compteur); 	//on peut faire la division
                if( tab[0] > inter  ){					//on compare
                    tab[0] = inter  ;
                    tab[1] = j;
                }
                _p[i][j] =10;                           //on lib�re la case
                        }
        }
        return tab[1] ;									//on return l'indice de la colonne dans laquelle on va jouer
}

/*--------------------impl�mentation de l'algorithme pour que l'ordi gagne--------------------*/

int Partie :: Algorithme(int profondeur){

        int n;                                      //qui joue ? ordi (n=0) ou joueur (n=1) ?
        int col[7] = {0,0,0,0,0,0,0};               //stocke pour chaque colonne j la ligne dans laquelle on peut jouer
        int tab=0;

        if(profondeur % 2 != 0){                    //c'est au tour de qui de jouer ?
            n=1;                                    //c'est au joueur
        }else{
            n=0;                                    //c'est � l'ordi
        }

        for(int j = 0 ; j <= 6 ; j++) col[j]=coupJouable(j); //la ligne dans laquelle on peut jouer en colonne j

        for(int j = 0 ; j <= 6 ; j++){

            if(col[j] != -1){                               //on peut jouer en colonne j

                _p[col[j]][j]=n;                            //on joue le coup

                if( vainqueur() != 10 ){                    //il y a un vainqueur
                    addCompteur(1);                         //on incr�mente le compteur de victoire
                    if(n==0){
                        addValeur(1);                       //on incr�mente le compteur de r�ussite de l'ordi
                    }else{
                        subValeur(1);                       //on d�sincr�mente le compteur de r�ussite de l'ordi
                    }

                    _p[col[j]][j]=10;                       //on lib�re la case
                    return -1;								//on s'arr�te dans l'algorithme
                }
                _p[col[j]][j]=10;                           //on lib�re la case
            }
        }

        if(profondeur <= level){                            //on n'a pas encore atteint la profondeur voulue
			int first=0;									//on n'est rentr� dans aucune colonne
            for(int j = 0 ; j <= 6 ; j++){					//on parcourt les colonnes

                int inter=0;								//r�initialisation de notre variable

                if( col[j] != -1 ){							// on peut jouer dans la colonne
					first++;								//on incr�mente notre compteur
                    _p[col[j]][j]=n;						//on joue le coup
                    inter = Algorithme(profondeur+1);		//on r�appelle la fct avec une profondeur de plus
                    if(first == 1)   tab = inter;			//on est au moins rentr� une fois dans une colonne : initialisation de inter
                    if(tab < inter)   tab = inter; 			//on compare les valeurs
                    _p[col[j]][j]=10;						//on lib�re la case
                }
            }
        }
        return -tab;

}
