#include "randomwalk.h"

RandomWalk :: RandomWalk(int P) :   
   rnd()
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
  	 
  	 _P = P;
     _x = new point[P];
     _dist = new double [P];
     
     
     _x[0].x=0;
     _x[0].y=0;
     _x[0].z=0;
    };
    
RandomWalk :: ~RandomWalk(){};

void RandomWalk :: Passo_lattice(){ //muove di P passi
    int x;
    double y;
    
    for(int i = 1; i<_P; i++){
        x = rnd.Rannyu(0,3);
        y = rnd.Rannyu(-1,1);
        
        _x[i] = passo_lattice(_x[i-1], x, y);
    }
};

void RandomWalk :: Passo_space(){ //muove di P passi
    vector v;
    for(int i = 1; i<_P; i++){
        v.phi = rnd.Rannyu(0, 2*M_PI);
        v.theta = funzionetheta();
        _x[i] = passo_space(_x[i-1], v);
    }
};

void RandomWalk :: AnalisiDist(){
    for(int i = 0; i<_P;  i++)
        _dist[i] = dist2(_x[i]);
    
};

void RandomWalk :: New(){
    delete [] _x;
    delete [] _dist;
    
    _x = new point[_P];
    _dist = new double [_P];
};
    


point RandomWalk :: passo_lattice(point r, int x, double y){    //muove di uno il punto

    if( x ==0){
        if(y >= 0)
            r.x += 1;
        if (y<0)
            r.x -=1;
    }
    if( x ==1){
        if(y >= 0)
            r.y += 1;
        if (y<0)
            r.y -=1;
    }
    if( x ==2){
        if(y >= 0)
            r.z += 1;
        if (y<0)
            r.z -=1;
    }
    
    return r;
};

point RandomWalk :: passo_space(point r, vector v){

    r.x += sin(v.theta)*cos(v.phi);
    r.y += sin(v.theta)*sin(v.phi);
    r.z += cos(v.theta);
    
    return r;
};

double RandomWalk :: funzionetheta(){
    
    double x = rnd.Rannyu();
    
    return acos (1-2*x);
}

double RandomWalk :: dist2( point p){
        return p.x*p.x + p.y*p.y + p.z*p.z;
};





        
