#include "integrale.h"

Integrale :: Integrale() :
    rnd(),
    _I(0)
    {
      //parte di codice per la generazione numeri random
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
    };

Integrale :: ~Integrale(){}

void Integrale :: UniformSampling(int N){
    double x;

    for(int i=0; i<N; i++){
            x = rnd.Rannyu();
            _I += funzione(x);    //somma prograssiva della funzione
    }
    
    _I /=N; //valore integrale            
}

void Integrale :: ImportanceSampling(int N){
        
    double x, y;
    
    for(int i=0; i<N; i++){
            x = rnd.Rannyu();
            y = funzione2(x);   //estraggo y con una p(x) scelta
            _I += funzione(y)/funzione3(y);    //somma prograssiva della funzione
    }
    
    _I /= N;
}


double Integrale :: funzione(double x){
    return (M_PI/2)*cos(x*M_PI/2);
}

double Integrale :: funzione2(double x){
    
    return (sqrt(1-x) + 1);
}

double Integrale :: funzione3(double x){
    
    return  2* (1- x);
}
