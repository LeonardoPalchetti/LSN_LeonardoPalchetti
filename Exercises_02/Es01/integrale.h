#ifndef __Integrale__
#define __Integrale__

#include <cmath>
#include "random.h"
#include <fstream>
#include <iostream>

using namespace std;

class Integrale {
    
protected:
    Random rnd;
    double _I;
    
public:
    Integrale();
    ~Integrale();
    
    
    void UniformSampling( int ); //esegue UniformSampling con un numero N di punti
    void ImportanceSampling( int ); //esegue ImportanceSampling con un numero N di punti
    
    double GetI(){return _I;}; //restituisce il valore dell'integrale
    double funzione(double);    //integranda UniformSampling
    double funzione2(double);   //inversa della p(x)
    double funzione3(double);   //p(x) per il calcolo della importance sampling
    void New(){_I = 0;};
};


#endif 
