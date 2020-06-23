#ifndef __BlackScholes__
#define __BlackScholes__

#include <string>
#include <cmath>
#include "random.h"
#include "metBlocchi.h"
#include <fstream>
#include <iostream>

using namespace std;

class BlackScholes{
    
protected:
    Random rnd;
    //PARAMETERS
    int _So;
    double _T;
    int _K;
    double _r;
    double _s;
    double *_S;
    int _step;
    
public:
     BlackScholes(int, double, int, double, double); //vuole So, T, K, r, s
     ~BlackScholes();
     
     
    void Diretto(int, int, std::string); //richiede numero di tiri totali, numero di blocchi e nome del file dove mettere i risultati
    void Progressivo(int, int, int, std::string) ;//richiede numero di tiri totali, numero di blocchi, numero di step e nome del file dove mettere i risultati
     
    void SetStep(int step){_step = step;};
    void Esegui(); //esegue blackscholes andando a dividere l'intervallo temporale per N.
    double Call();
    double Put();
    void New(){ delete [] _S;}; 
    
    double max(double, double);  //trova il massimo fra due numeri
};


#endif 

