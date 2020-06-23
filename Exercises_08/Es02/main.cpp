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

    output.open("RisultatiMinimazione.dat", ios::out);
    
    nsteps = P/npara; //numero di valutazioni per ogni coppia di parametri
    
    for(ibeta = 0; ibeta < nbeta; ibeta++){
        for(ipara = 0; ipara < npara; ipara++){
            
            Equilibration(1.25); //per ogni nuovo parametro porto sistema all'equilibrio.
            
            for(isteps = 0; isteps < nsteps; isteps++){
                Move(1.25);
            
                Metropolis(); //metropolis sul f trial
                
                Enew += H(x); //sommo valori Energia per i parametri;
                
            }
            Enew /=nsteps;  //media delle energie
            
            MetropolisPara(); //algoritmo di metropolis per i parametri;
            
            if(ibeta != nbeta - 1 && ipara != npara - 1) MovePara(0.5,0.2);
        }
        
        cout << "Eseguito  " << ibeta + 1  << "/" << nbeta << endl;
        
        //E[ibeta] = Eold;
        
        output << ibeta + 1 << "   " << Eold << "   " << mu << "   " << sigma << endl;
        
        Beta += dB;
    }
    
    output.close();
      
    cout << endl << "Energia minima : " << Eold << " trovata con la coppia ( " << mu << " ; " << sigma << " )" << endl;
    
    
//##################### Eseguo misure con i valori minimizzati ##############################//

    cout << endl << "Eseguo misure con i valori minimizzati" << endl;
    
    nsteps = P/nblk; //numero di valutazioni per ogni blocco
    
    output.open("coordinateX.dat", ios::out);
    for( iblk=0; iblk<nblk; iblk++){
        for(isteps = 0; isteps < nsteps; isteps++){
            Move(1.25);
            
            Metropolis(); //metropolis sul f trial
            output << x <<  endl; //mi segno su file la posizione
            
            
            E[iblk] += H(x); //calcolo H
            
        }
        E[iblk] /= nsteps;
    }
        
    output.close(); 
    
    MB.Analisi(E, "misureEnergia.dat");
                
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
    Beta = 5;
    dB= 5;
    
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

void MovePara(double b, double a){
    //cambio i parametri mu e sigma;
    mu_old = mu;
    sigma_old = sigma;
    
    mu_new = mu + rnd.Rannyu(-b,b);
    sigma_new = max(0.1, sigma + rnd.Rannyu(-a,a));
    
    mu = mu_new;
    sigma = sigma_new;
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


void MetropolisPara(){
    double A;
    double B;
    double pold = 1, pnew = 1;
    if(ibeta == 0 && ipara ==0) { Eold = Enew;}
    
    else{
        pold = exp(-Eold*Beta);
        pnew = exp(-Enew*Beta);

        A = min(1, pnew/pold);
        B = rnd.Rannyu();
    
        if ( A >= B ){ 
            mu = mu_new;
            sigma = sigma_new;
            Eold = Enew; //mi salvo l'energia nuova
        }
    
        else{
            mu = mu_old;
            sigma = sigma_old;
            //l'energia rimane quella vecchia.
        }
    }
}


//funzioni metropolis

//f trial = f_pos + f_neg
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
    f = f_pos(x) + f_neg(x); //funzione f
    
    V = x*x*x*x - 2.5*x*x; //potenziale
     
    der = (-1/s2)*f + (1/(s2*s2))* ((x-mu)*(x-mu)*f_neg(x) + (x+mu)*(x+mu)*f_pos(x)); //derivata seconda di f
    
    
    return -0.5*der + V*f;
    
}; // (Hf)x

double H(double x){
    
    double Hf;
    double f;
    
    Hf = H_trial(x);
    f = f_pos(x) + f_neg(x);
    
    return Hf/f;
}; //mi calcola valor medio di H;


//calcolo massimo e minimo
double min (double a, double b){
    
    if (a > b) return b;
    else return a;
};

double max (double a, double b){
    
    if (a < b) return b;
    else return a;
};
