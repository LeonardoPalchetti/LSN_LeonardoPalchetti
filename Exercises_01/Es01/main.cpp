#include <iostream>
#include "random.h"
#include <fstream>
#include <cmath>

using namespace std;

double error(double, double, int);	//funzione calcolo errore


int main(){

	int M = 10000; //numero totale di tiri
	int N = 100;	//numero di blocchi
	int L = M/N;	// numero di tiri in ogni blocco
	double n[M]; //def n := array di numeri random [0,1]
	double av[M], av2[M]; //array delle misure, e del rispettivo quadrato per i blocchi
    double sv[M], sv2[M]; //array delle varianze delle misure, e del rispettivo quadrato per i blocchi
	double av_prog[M], av2_prog[M], err[M]; //medie progressive dei tiri e rispettivo errore
	double sv_prog[M], sv2_prog[M], serr[M]; //medie progressive della varianza dei tiri e rispettivo errore	
	double sum, sums;
	fstream output;
	Random rnd;

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
  	 } else cerr << "PROBLEM: Unable to open seed.in" << endl; //fine preparazione

	for(int i=0; i<M; i++) //tiri random
		n[i] = rnd.Rannyu();
			
	for(int i=0; i<N; i++){ //misure blocchi
		sum = 0;
        sums = 0;
		for (int j=0; j<L; j++){
			sum += n[j+i*L];
            sums += ( n[j+i*L] - 0.5)*( n[j+i*L] - 0.5);
        }
		av[i] = sum/L;
		av2[i] = av[i]*av[i];
        sv[i] = sums/L;
		sv2[i] = sv[i]*sv[i];
	 }

	output.open("misure.dat", ios::out);	// file dove inserire dati
	for(int i=0; i<N; i++){			//calcolo delle medie proggressive
		for(int j=0; j<i+1; j++){
			av_prog[i] += av[j];
            av2_prog[i] += av2[j];
            sv_prog[i] += sv[j];
            sv2_prog[i] += sv2[j];
		}
		av_prog[i] /= (i+1);
		av2_prog[i] /= (i+1);	
		err[i] = error( av_prog[i], av2_prog[i], i);
        sv_prog[i] /= (i+1);
		sv2_prog[i] /= (i+1);	
		serr[i] = error( sv_prog[i], sv2_prog[i], i);
		
		output << av_prog[i] <<  " " <<  err[i] <<  " " << sv_prog[i] <<  " " <<  serr[i] << endl; //inserisco dati nel file

	}

	output.close();
    
    //test del chi-quadro
    
    int M1 = 100;         //sottointervalli di [0,1]
    int N1 = 10000;     //lanci nell'intervallo [0,1]
    double L1 = double(M1)/double(N1); //larghezza intervalli
    double *t;         //:= puntatore di numeri random [0,1]
    double n1[M1]; //:= array di numero di lanci in ogni intervallo 
   //double av_n[M1]; //:= array delle medie del numero di lanci in ogni intervallo
    double a; //contatore
    double x[100]; //:= array dei chi-quadri
    fstream chi2;
    
    
        chi2.open("chi2.dat", ios::out);
       for(int b=0; b< 100; b++) {
             
            t = new double[N1];

        for(int i=0; i<N1; i++) //tiri random
		t[i] = rnd.Rannyu();
     
           for(int i=0; i<M1; i++) {//conteggio lanci in ogni intervallo
                a = 0;
                for(int j=0; j<N1; j++) { //tiri random
                        if( i*L1 <= t[j] && t[j] < L1*(1+i))
                        a++;
                n1[i] = a;
            }               
        }

            
            for(int i=0; i<M1; i++)
                x[b] += ((n1[i] - double(N1/M1))*(n1[i] - double(N1/M1)))/double(N1/M1); //calcolo del chi-quadro
        
            chi2 << x[b] << endl;
                  
            delete [] t;
            
       }

       chi2.close();
	return 0;

}	


double error (double av, double av2, int n){ //funzione che calcola l'errore
    if (n==0)
        return 0;
    else
        return sqrt((av2 - av*av)/n);
	}

	

