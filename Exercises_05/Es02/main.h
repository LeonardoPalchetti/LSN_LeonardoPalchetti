#ifndef __MAIN__
#define __MAIN__

#include <stdlib.h>
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow

#include "random.h"
#include "metBlocchi.h"
struct point {
    double x, y, z; // cordinate punto
};

//parametri blocchi
int P = 1000000;//numero di tiri(passi)
const int M = 100; //numero di blocchi 
int N = P/M;
MetBlocchi MB(M);

double r1[M], r2[M]; //calcolo della media di r.
point p, pold, pnew; // punti nello spazio cartesiano
double C; //contatore accettanza
//Random
Random rnd;


//funzioni 
void Input();
void Move(double);
void Metropolis(int);
void Equilibration(double, int);


//funzioni Metropolis
double f_orbital(point);
double s_orbital(point);
double pf(double);
double ps(double);
double min(double, double);



#endif 
