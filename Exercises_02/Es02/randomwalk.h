#ifndef __Integrale__
#define __Integrale__

#include <cmath>
#include "random.h"
#include <fstream>
#include <iostream>

using namespace std;

struct point {
    double x, y, z; // cordinate punto
};

struct vector{
    double r;
    double theta, phi;
    };

class RandomWalk {
    
protected:
    point *_x;
    int _P;
    double *_dist;
    Random rnd;
        
        
public:
    RandomWalk(int); //genera un randomwalk lungo P passi dall'origine
    ~RandomWalk();
    
    void Passo_lattice(); //esegue P passi nel reticolo
    void Passo_space(); //esegue P passi nello spazio
    
    void AnalisiDist(); //esegue l'Analisi delle distanze
    double GetDist(int i){return _dist[i];}; //restituisce la i-esima distanza
    void New();
    
    double dist2( point); // funzione calcola distanza al quadrato dall'origine del punto p
    point passo_lattice(point, int, double); //funzione randomwalk nel reticolo unitario
    point passo_space(point, vector); //funzione randomwalk nello spazio
    double funzionetheta(); //funzione calcola componente theta dell'angolo solido
    
};


#endif 
