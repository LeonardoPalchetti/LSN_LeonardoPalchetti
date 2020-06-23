#include <iostream>
#include "random.h"
#include <fstream>
#include <cmath>

using namespace std;

int main(){

    int T=10000; // numero di misure 
    double Sx[T], Sy[T], Sz[T]; // := array delle somme di variabili random standard, esponenziale, lorentziana
    fstream dati, dati1, dati2, dati3;
	Random rnd;
    {       //parte di codice per la generazione numeri random
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
    }
  	 
  	 
     dati.open("N1.dat", ios::out);      //apro file con N=1
     dati1.open("N2.dat", ios::out);      //apro file con N=2
     dati2.open("N10.dat", ios::out);      //apro file con N=10
     dati3.open("N100.dat", ios::out);      //apro file con N=100
  	 for(int i=0; i<T; i++){
        for(int j=0; j<100; j++){
             Sx[i] += rnd.Rannyu();
             Sy[i] += rnd.Exponential(1);  //numero random esponenziale
             Sz[i] += rnd.Lorentz(1,0);     //numero random lorenzt
                      
            if(j==0)     
                dati << Sx[i] << " " << Sy[i] << " " << Sz[i] << endl;                      //media su 1 elemento
            if(j==1)
                dati1  << Sx[i]/2 << " " << Sy[i]/2 << " " << Sz[i]/2 << endl;         //media su 2 elementi
            if(j==9)
                dati2 << Sx[i]/10 << " " << Sy[i]/10 << " " << Sz[i]/10 << endl;    //media su 10 elementi
            if(j==99)    
                dati3 << Sx[i]/100 << " " << Sy[i]/100 << " " << Sz[i]/100 << endl;  //media su 100 elementi
        }         
     }
     
    dati.close();
    dati1.close();
    dati2.close();
    dati3.close();


	return 0;

}	

    

