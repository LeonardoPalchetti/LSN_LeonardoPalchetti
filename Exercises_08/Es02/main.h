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
int npara = 100; //numero di parametri per l'energia
int nsteps; //numero di tiri per valutazione dell'energia
int nbeta=100; //numero di temperature per il sampling
int ipara, isteps, ibeta;

const int nblk = 100;
int iblk;
MetBlocchi MB(nblk);

//parametri f_Trial
double mu, sigma;
double mu_new, sigma_new;
double mu_old, sigma_old;

double Beta, dB; //temperatura fittizia

double E[nblk]; //calcolo della media di H
double Enew, Eold; //valuto energia
double x, xold, xnew; // punti nello spazio cartesiano

//Random
Random rnd;


//funzioni 
void Input();
void Move(double);
void MovePara(double, double);
void Metropolis();
void MetropolisPara();
void Equilibration(double);


//funzioni Metropolis
double f_pos(double); // f+
double f_neg(double); // f-
double p_trial(double); //probabilità
double H_trial(double); // (Hf)x

double H(double); //mi calcola valor medio di H;
double min(double, double);
double max(double, double);


#endif 
