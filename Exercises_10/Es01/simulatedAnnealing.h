#ifndef __SimulatedAnnealing__
#define __SimulatedAnnealing__

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

class SimulatedAnnealing{
    
protected:
    //classi
    Random rnd;

    //variabili per la mappa;
    city *map;
    //varibili percorso
    int *percorso;
    int n_cities;
    double _L;
    
    //varibili __SimulatedAnnealing__
    double Beta;
    double dB;
    
    
public:
    SimulatedAnnealing(int);
    ~SimulatedAnnealing();
    
   double Lunghezza(int *);
   void Evoluzione();
   void Metropolis(int *, double);
   double min(double, double);
   void Tempering();
   void Delete();   
   
    //mutazioni
    void Permutazione(int *);
    void Esegui(int *);
    void PairPermutation(int *); //scambia due città
    void Shift(int *); //shifta le città
    void BlockPermutation(int *); //scambia blocchi di citta
    
    //soluzione
    double GetX(int);
    double GetY(int);
    int GetName(int);
    double GetL(){return _L;}; //ritorna la lunghezza del percorso
    
};
#endif 
