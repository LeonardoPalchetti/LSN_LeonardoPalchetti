#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "main.h"

using namespace std;

int main(int argc,char **argv){ 
    
    fstream output;
    
    if(argc != 2){
        cout << "ERROR! Mi servono le cordinate (x) del punto iniziale!" << endl;
        return -1;
    }
    
    Input();
    
    x=atoi(argv[1]);
    C=0;
    
    //Equilibration(1.25);
    
    output.open("coordinateX.dat", ios::out);
    for(int i=0; i<M; i++){
        for(int j=0; j < N ; j++){
            Move(1.25);
            
            Metropolis(); //metropolis sul f trial
    
            if(x == xnew ) C += 1;
            
            output << x <<  endl; //mi segno su file la posizione
            
            
            E[i] += H(x); //calcolo H
            
        }
        E[i] /= N;
    }
        
    output.close(); 
    
    cout << C/double(N*M);
    if( C/(N*M) > 0.5) cout << "  che è maggiore di 1/2" << endl;
    if( C/(N*M) < 0.5) cout << "  che è minore di 1/2" << endl;    
    
    MB.Analisi(E, "misureH.dat");
    return 0;
}

void Input(){ 
    //parte di codice per la generazione numeri random
    {
   	int seed[4]; //preparo il generatore di numeri random
   	int p1, p2;
   	ifstream Primes("Primes");
 	if (Primes.is_open()){
  	    Primes >> p1 >> p2 ;
  	 }else cerr << "PROBLEM: Unable to open Primes" << endl;
   	Primes.close();

   	ifstream input("seed.in");
   	string property;
   	if (input.is_open()){
      		while ( !input.eof() ){
        	 	input >> property;
        		 if( property == "RANDOMSEED" ){
        	 	  input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
        		  rnd.SetRandom(seed,p1,p2);
        	 }
     	 }
      		input.close();
  	 } else cerr << "PROBLEM: Unable to open seed.in" << endl;
    }
    //fine preparazione
    
    
    //Iniaizalizzo la f trial;
    mu = 1;
    sigma = 0.5;
    
    
}


void Equilibration(double a){
    double stop = 1000;
    for (int i=0; i< stop; i++){
        Move(a);
        Metropolis();
    }
}

void Move(double b){
    xold = x;
    xnew = x + rnd.Rannyu(-b,b);
}

void Metropolis(){
    double A;
    double B;
    double pold = 1, pnew = 1;
    
    pold = p_trial(xold);
    pnew = p_trial(xnew);

    A = min(1, pnew/pold);
        
    B = rnd.Rannyu();
        
    if ( A >= B ) x = xnew;
}

//funzioni metropolis
double f_pos(double x){
    
    double s2 = sigma*sigma;
    double X;
    
    X = (x+mu)*(x+mu);
    X = X/(2*s2);
    
    return exp(-X);
};

double f_neg(double x){
    
    double s2 = sigma*sigma;
    double X;
    
    X = (x-mu)*(x-mu);
    X = X/(2*s2);
    
    return exp(-X);
};
double p_trial(double x){
    double f =  f_pos(x) + f_neg(x);
    
    return f*f;
}; //probabilità

double H_trial(double x){

    double der;
    double V;
    double f;
    double s2;
    
    
    s2 = sigma*sigma;
    f = f_pos(x) + f_neg(x);
    
    V = x*x*x*x - (5/2)*x*x; //potenziale
     
    der = (-1/s2)*f + (1/(s2*s2))* ((x-mu)*(x-mu)*f_neg(x) + (x+mu)*(x+mu)*f_pos(x)); //derivata seconda di f
    
    return (-1/2)*der + V*f;
    
}; // (Hf)x

double H(double x){
    
    double Hf;
    double f;
    
    Hf = H_trial(x);
    f = f_pos(x) + f_neg(x);
    
    return Hf/f;
}; //mi calcola valor medio di H;



double min (double a, double b){
    
    if (a > b) return b;
    else return a;
};

    
