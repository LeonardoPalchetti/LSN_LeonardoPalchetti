#ifndef __Population__
#define __Population__

#include <stdlib.h>
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "random.h" //generatore random

struct city{
    //coordinate
    double x;
    double y;
    
    //label
    int name; 
};

class Population{
    
protected:
    //classi
    Random rnd;

    //variabili per la mappa;
    city *map;
    //varibili popolazione
    int *antenato; //percorso di partenza
    int  n_cro; //numero di cromosomi
    int n_gen; //numero di geni
    int **popolazione;
    double *lunghezza;
    //variabili evoluzione
    int *mamma;
    int *babbo;
    int *soluzione;
    
public:
    Population(int, int, int); //genera un popolazione (numero cromosomi, numero geni)
    ~Population();
    
    //metodi popolazione
    void Evoluzione();
    void BigBang();
    int RouletteTruccata();
    void Lunghezza();
    void Ordina();
    void Scambia(int *);
    
    //mutazioni
    void Crossover();
    void Permutazione(int *);
    void Esegui(int *);
    void PairPermutation(int *); //scambia due città
    void Shift(int *); //shifta le città
    void BlockPermutation(int *); //scambia blocchi di citta
    void Sostituisci(int *);

    
    //informazioni popolazione
    double GetX(int);
    double GetY(int);
    int GetName(int);
    double GetLunghezza(int pos){return lunghezza[pos];}; //ritorna la lunghezza di un certo percorso
    void GetSolution(); //da la posizione della soluzione
    double BestMedia();
    int Invia(int i){return popolazione[0][i];};
    void Delete();
    
};
#endif 
