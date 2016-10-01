#ifndef Partie_h
#define Partie_h

class Partie{

    public :

        int _compteur;              // compte le nb de victoires dans l'IA
        int _valeur;                // compte le nb de victoire de l'ordi dans l'IA
        int _gain;                  // nb de parties gagnées par l'ordi
        int _perte;                 // nb de parties perdues par l'ordi
        int _nul;                   // compte le nb de parties qui aboutissent à un match nul
		bool _fin;					// _fin détermine si un alignement de 4 pions ou plus a été réalisé
        int _p[6][7];               // plateau du jeu de puissance 4 (6 lignes, 7 colonnes)

    Partie(int c=0,int v=0,int g=0,int p=0,int nombre=0,bool f=false);
    ~Partie();
	Partie(const Partie &source);

    int getCompteur();
    int getValeur();
    int getGain();
    int getPerte();
    int getNul();
	int getFin();

    void setCompteur(int c);
    void setValeur(int v);
    void setGain(int g);
    void setPerte(int p);
    void setNul(int nombre);
	void setFin(bool f);

    void addCompteur(int c);
    void addValeur(int v);
    void addGain(int g);
    void addPerte(int p);
    void addNul(int nombre);

    void subCompteur(int c);
    void subValeur(int v);

    void raz();
    int coupJouable(int j);
    bool rempli();
    int vainqueur();
    void affichage();
    void coup(int n);
    int IA();
    int Algorithme(int profondeur);
};
#endif
