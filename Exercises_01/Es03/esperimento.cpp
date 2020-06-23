#include "esperimento.h"


using namespace std;

Esperimento :: Esperimento():
    rnd(),
    _hits(0)
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
    
Esperimento :: ~Esperimento(){};

void Esperimento :: Esegui(){
        _n.x1[0] = rnd.Rannyu();   //lancio primo vertice
        _n.x1[1] = rnd.Rannyu();
        _n.cos = rnd.Cos();   //lancio angolo secondo vertice
        _n.x2[0] = _n.x1[0] + _n.L*_n.cos;
        _n.x2[1] = _n.x1[0] + _n.L*sqrt(1-_n.cos*_n.cos);    //trovo secondo vertice (non importa se il seno è positivo o negativo, stesso risultato
            
        if(_n.x1[0] == 0 || _n.x2[0] <= 0)        //cerco intersezioni, conto anche se escono dal foglio
            _hits++;
        else if(_n.x1[0] < _n.x2[0]){
            for(int c=0; c<11; c++){
                if(_n.x1[0] < _D*c && dist(_n.x1[0], _D*c) <= dist(_n.x1[0],_n.x2[0]))
                    _hits++;
                }
           }
        else if(_n.x1[0] > _n.x2[0]){
            for(int c=0; c< 11; c++){
                if(_n.x2[0] < _D*c && dist(_n.x2[0], _D*c) <= dist(_n.x1[0],_n.x2[0])) 
                    _hits++;
                }
            }
}
    
void Esperimento :: Analisi(double E){
            _PI = (2*_n.L*E)/(_D*Hits());
}

double Esperimento :: dist( double x, double y){
    return abs(x-y);
}
