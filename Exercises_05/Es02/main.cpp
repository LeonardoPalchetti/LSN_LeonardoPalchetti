#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "main.h"

using namespace std;

int main(int argc,char **argv){ 
    
    fstream output;
    
    if(argc != 4){
        cout << "ERROR! Mi servono le cordinate (x,y,z) del punto iniziale!" << endl;
        return -1;
    }
    
    Input();
    
////############################ PRIMO ORBITALE #####################################
    p.x=atoi(argv[1]);
    p.y=atoi(argv[2]);
    p.z = atoi(argv[3]);
    
    C=0;
    
    Equilibration(0.75,1);
    
    output.open("coordinateP1.dat", ios::out);
    for(int i=0; i<M; i++){
        for(int j=0; j < N ; j++){
            Move(0.75); //per il gauss lo centro nel punto e muovo in un intorno
            
            Metropolis(1); //metropolis sul primo orbitale
    
            if(p.x==pnew.x && p.y==pnew.y && p.z==pnew.z ) C += 1;
            
            output << p.x << " " << p.y << " " << p.z << endl; //mi segno su file l
            r1[i] += sqrt(p.x*p.x+p.y*p.y+p.z*p.z); //calcolo distanza punto
        }
        r1[i] /= N;
    }
        
    output.close(); 
    
    cout << C/double(N*M);
    if( C/(N*M) > 0.5) cout << "  che è maggiore di 1/2" << endl;
    if( C/(N*M) < 0.5) cout << "  che è minore di 1/2" << endl;    
    
    MB.Analisi(r1, "misureR1.dat");
//############################ SECONDO ORBITALE #####################################
    p.x=atoi(argv[1]);
    p.y=atoi(argv[2]);
    p.z = atoi(argv[3]);
    
    C=0;
    
    Equilibration(1.75,2);
    
    output.open("coordinateP2.dat", ios::out);
    for(int i=0; i<M; i++){
        for(int j=0; j < N ; j++){
            Move(1.75);
            
            Metropolis(2); //metropolis sul secondo orbitale
    
            if(p.x == pnew.x && p.y == pnew.y && p.z==pnew.z ) C += 1;
            
            output << p.x << " " << p.y << " " << p.z << endl; //mi segno su file 2
            r2[i] += sqrt(p.x*p.x+p.y*p.y+p.z*p.z); //calcolo distanza punto
        }
        r2[i] /= N;
    }
        
    output.close(); 
    
    cout << C/double(N*M);
    if( C/(N*M) > 0.5) cout << "  che è maggiore di 1/2" << endl;
    if( C/(N*M) < 0.5) cout << "  che è minore di 1/2" << endl;    
    
    MB.Analisi(r2, "misureR2.dat");   
    
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
}


void Equilibration(double a, int b){
    double stop = 1000;
    for (int i=0; i< stop; i++){
        Move(a);
        Metropolis(b);
    }
}

void Move(double sigma){
    pold = p;
    
    pnew.x = p.x + rnd.Gauss(0,sigma);
    pnew.y = p.y + rnd.Gauss(0,sigma);
    pnew.z = p.z + rnd.Gauss(0,sigma);
}

void Metropolis(int _orbitale){
    double A;
    double B;
    double px = 1, py = 1;
    
    
    if(_orbitale == 1){
        px = f_orbital(pold);
        py = f_orbital(pnew);
        
        px = pf(px);
        py = pf(py);
    }
    if(_orbitale == 2){
        px = s_orbital(pold);
        py = s_orbital(pnew);
        
        px = ps(px);
        py = ps(py); 
    }
    A = min(1, py/px);
        
    B = rnd.Rannyu();
        
    if ( A >= B ) p = pnew;
}

//funzioni metropolis
double f_orbital(point r){
    
    double p = sqrt(r.x*r.x + r.y*r.y + r.z*r.z);
    return exp(-p);
};

double pf (double f){
    
    return (1./M_PI)*f*f;
};

double s_orbital(point r){
    
    double p = sqrt(r.x*r.x + r.y*r.y + r.z*r.z);
    
    return (1./8)*exp(-p/2)*r.z;
};

double ps (double f){
    
    return (2./M_PI)*f*f;
};

double min (double a, double b){
    
    if (a > b) return b;
    else return a;
};

    
