#include "blackscholes.h"
#include <fstream>
#include <iostream>

BlackScholes :: BlackScholes(int So, double T, int K, double r, double s) :
    rnd(),
    _So(So),
    _T(T),
    _K(K),
    _r(r),
    _s(s)
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
    
BlackScholes :: ~BlackScholes(){};

void BlackScholes :: Diretto(int N, int M, string nomefile){
    int L = N/M;
    double C[M], P[M]; //call and put

    MetBlocchi MB(M);
    
    SetStep(1);
    
    for(int a=0; a<M; a++){ //calcolo di C e P nei blocchi
        C[a] = 0;
        P[a] = 0;
        for(int i=0; i<L; i++){
            Esegui();
            C[a] += Call();
            P[a] += Put();
            New();
        }
        
        C[a] /= L;
        P[a] /= L;
    }
    
    MB.Analisi(C, nomefile + "C.dat");
    MB.Analisi(P, nomefile + "P.dat");

};

void BlackScholes :: Progressivo(int N, int M, int step, string nomefile){
    int L = N/M;
    fstream output;
    double C[M], P[M]; //call and put 

    
    MetBlocchi MB(M);
    
    SetStep(step);
    
    for(int a=0; a<M; a++){     //calcolo di C e P nei blocchi
        C[a] = 0;
        P[a] = 0;
        for(int i=0; i<L; i++){
            Esegui();
            C[a] += Call();
            P[a] += Put();
            New();
        }
        
        C[a] /= L;
        P[a] /= L;
    }
    
    MB.Analisi(C, nomefile + "C.dat");
    MB.Analisi(P, nomefile + "P.dat");
};

void BlackScholes :: Esegui(){  //step deve essere maggiore di 0
    
    double Z, x; //incremento e varibile ausiliaria
    _S = new double[_step];  //creo un vettore a seconda del calcolo diretto
    
    if(_step==1){
            Z = rnd.Gauss(0,1);
            x = ((_r - (_s*_s)/2)*_T + _s*Z*sqrt(_T));
            _S[0] = _So*exp(x);
    }
    
    else{
        _S[0] = _So;
        for(int j=1; j<_step; j++){
            Z = rnd.Gauss(0,1);
            x = (_r - (_s*_s)/2)*(_T/double(_step)) + _s*Z*sqrt(_T/double(_step));
            _S[j] = _S[j-1]*exp(x);
        }
    }
};

double BlackScholes :: Call(){
    return exp(-_r*_T)*max(0, _S[_step - 1] - _K);
};

double BlackScholes :: Put(){
    return exp(-_r*_T)*max(0, _K - _S[_step - 1]);
};
 
double BlackScholes :: max (double a, double b){
        if(a > b)
            return a;
        else
            return b;
};        
            
            
            
            
            
            
