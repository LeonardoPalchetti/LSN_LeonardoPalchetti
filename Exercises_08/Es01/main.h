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
int T = 1000000;//numero di tiri(passi)
const int M = 100; //numero di blocchi 
int N = T/M;
MetBlocchi MB(M);

//parametri f_Trial
double mu, sigma;


double E[M]; //calcolo della media di H
double x, xold, xnew; // punti nello spazio cartesiano
double C; //contatore accettanza
//Random
Random rnd;


//funzioni 
void Input();
void Move(double);
void Metropolis();
void Equilibration(double);


//funzioni Metropolis
double f_pos(double); // f+
double f_neg(double); // f-
double p_trial(double); //probabilità
double H_trial(double); // (Hf)x

double H(double); //mi calcola valor medio di H;
double min(double, double);



#endif 
