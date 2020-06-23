#include "simulatedAnnealing.h"

using namespace std;

SimulatedAnnealing :: SimulatedAnnealing(int NCIT):
    rnd(),
    n_cities(NCIT)
    {
        //parte di codice per la generazione numeri random
   	int seed[4]; //preparo il generatore di numeri random
   	int p1, p2;
   	ifstream Primes("Primes");
 	if (Primes.is_open()){
        //for(int i=0; i<3; i++)
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
  	 
    double x, y;
    
    map = new city[n_cities]; //il numero dei geni è uguale al numero delle città
    
    percorso = new int[n_cities]; 
    
    for(int icity = 0; icity < n_cities; icity++){        
      x = rnd.Rannyu(-1,1);
      y = rnd.Rannyu(-1,1);
      
      if(y >= 0) y = sqrt(1-x*x);
      else y = -1*sqrt(1-x*x);
          
      map[icity].x = x;
      map[icity].y = y;
      map[icity].name = icity + 1;
    }
    
    Beta = 1;
    dB = 10;
    
    Permutazione(percorso);
    
    _L = Lunghezza(percorso);
    
};
    
SimulatedAnnealing :: ~SimulatedAnnealing(){};
    
void SimulatedAnnealing :: Permutazione(int *percorso){
    
    percorso[0] = 1;
    
    for(int i = 1; i < n_cities; i++) percorso[i] = 0;
    
    int a;
    int b, c;
    
    for(int i = 1; i < n_cities; i++){
        a = i +1;
        b = 0;
        do{
            c = rnd.Rannyu()*(n_cities);
            if(percorso[c] == 0){
                percorso[c] = a;
                b = 1;
            }
        }while(b == 0);
    }
    
};
    
double SimulatedAnnealing :: Lunghezza(int *strada){
    
    double L;
    double dx = 0;
    double dy = 0;
    int pos1, pos2;
    
    L = 0;
    
    for(int  icity = 0; icity < n_cities; icity++){
        if( icity != n_cities - 1){
            pos1 = strada[icity] - 1; //il nome è posizione della mappa + 1;
            pos2 = strada[icity + 1] - 1;
        
            dx = abs(map[pos1].x - map[pos2].x);
            dy = abs(map[pos1].y - map[pos2].y);
        
            L += sqrt(dx*dx + dy*dy);
        }
        
        else{
            pos1 = strada[icity] - 1; //il nome è posizione della mappa + 1;
            pos2 = strada[0] - 1;
            
            dx = abs(map[pos1].x - map[pos2].x);
            dy = abs(map[pos1].y - map[pos2].y);
        
            L +=  sqrt(dx*dx + dy*dy);
            }
        }
        
     //trovo la lunghezza del percorso   
    return L;

};    
    
    
void SimulatedAnnealing :: Evoluzione(){
    
    int *nuovo;
    double Lnuovo;
    
    nuovo = new int[n_cities];
    
    
    for(int i = 0; i < n_cities; i++) nuovo[i] = percorso[i];
    
    
    Esegui(nuovo);
    
    Lnuovo = Lunghezza(nuovo);
    
    Metropolis(nuovo, Lnuovo);
    
    delete [] nuovo;
};


void SimulatedAnnealing :: Esegui(int *nuovo){

    double prob;
    
    prob = rnd.Rannyu();
    
    if( prob < 0.25) PairPermutation(nuovo);
    
    else if ( 0.25 <= prob && prob < 0.5 ) Shift(nuovo);
    
    else if ( 0.5 <= prob  && prob < 0.75)  BlockPermutation(nuovo);
    
    else if ( 0.75 <= prob  && prob < 1)  Permutazione(nuovo);
};

void SimulatedAnnealing :: PairPermutation(int *nuovo){
    
    int a, b;
    int fake;
    
    a = rnd.Rannyu()*n_cities;
    if(a == 0) a = 1;
    
    do{
    b = rnd.Rannyu()*n_cities; 
    
    if(b == 0) b = 1;
    }while(b != a);
    
    fake = nuovo[a];
    nuovo[a] = nuovo[b];
    nuovo[b] = fake;
    
};

void SimulatedAnnealing :: Shift(int *nuovo){
    
    int a, b;
    
    int fake[n_cities];
    
    a = rnd.Rannyu()*(n_cities/2);
    
    fake[0] = nuovo[0];
    
    for (int i = 1; i < n_cities; i ++){
        
        b = a +i;
        if( b >= n_cities ) b = b  - (n_cities - 1);
        
        fake[b] = nuovo[i];
    }
    
    nuovo = fake;
   
};

void SimulatedAnnealing :: BlockPermutation(int *nuovo){
    
    int a, b,c;
    int d, e; //servono per le condizioni al contorno
    
    int fake;
    
    a = rnd.Rannyu()*n_cities; //scelgo un elemento da scambiare con il suo blocco
    if(a == 0) a = 1;
    
    c = rnd.Rannyu()*int(n_cities/2);
   
    
    do{
    b = rnd.Rannyu()*n_cities; 
    
    if(b == 0) b = 1;
    }while(abs(b - a) < c );
    
    for(int i=0; i < c; i++){
        
        d = a+i;
        if( d >= n_cities ) d = d  - (n_cities - 1); //condizioni al contorno
        e = b+i;
        if( e >= n_cities ) e = e  - (n_cities - 1);
        
        
        fake = nuovo[d];
        nuovo[d] = nuovo[e];
        nuovo[e] = fake;
    }
   
};
    
void SimulatedAnnealing :: Metropolis(int *nuovo, double Lnuovo){
    double A;
    double B;
    double p = 1;
    double dL;
    
    dL = Lnuovo - _L;
    
    p = exp(-dL*Beta);
    
    A = min(1, p);
    B = rnd.Rannyu();
    
    if ( A >= B ){ 
            for(int i=0; i<n_cities; i++) percorso[i] = nuovo[i];
            _L = Lnuovo;
        }
};

double SimulatedAnnealing :: min (double a, double b){
    
    if (a > b) return b;
    else return a;
};

void SimulatedAnnealing :: Tempering(){
    
    Beta = Beta + dB;
};

double SimulatedAnnealing :: GetX(int pos){
    
    int nome;
    
    nome = percorso[pos];
    
    return map[nome - 1].x;
};
    
 double SimulatedAnnealing :: GetY(int pos){
    
    int nome;
    
    nome = percorso[pos];
    
    return map[nome - 1].y;
}; 


int SimulatedAnnealing :: GetName(int pos){
    
    int nome;
    
    nome = percorso[pos];
    
    return map[nome - 1].name;
}; 
    
void SimulatedAnnealing :: Delete(){
    
    delete [] percorso;
    delete [] map;
};
