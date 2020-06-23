#ifndef __Esperimento__
#define __Esperimento__

#include "random.h"
#include <iostream>
#include <cmath>
#include <fstream>

struct needle{
    double x1[2];   //punto primo vertice
    double cos = 0;     //coseno angolo secondo vertice
    double L = 0;        //lunghezza del'ago
    double x2[2]; //punto secondo vertice
};

class Esperimento {
    
protected: 
    Random rnd;
    int _hits; //contatore
    needle _n; 
    double _D; //distanza fra le righe
    double _PI;
    
public:
    //costruttore
    Esperimento();
    //distruttore
    ~Esperimento();
    
    //metodi();
    
    void Esegui();
    void Analisi(double);
    
    void New() {_hits = 0;};
    void SetL(double l) {_n.L = l;};
    void SetD(double d) {_D = d;};
    double Hits() {return _hits;};
    double PI(){return _PI;};
    
    double dist( double , double);      //funzione calcola distanza sulle x
    
};
#endif // __Esperimento__
