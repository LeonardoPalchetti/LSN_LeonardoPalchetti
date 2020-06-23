#include <iostream>
#include "random.h"
#include "integrale.h"
#include "metBlocchi.h"
#include <fstream>


using namespace std;


int main(){
    int T = 100000; //numero di lanci
    int M = 100; // numero di blocchi
    int L = T/M;
    double I[M];
    
    Integrale integral;
    MetBlocchi MB(M);
   
    for(int a=0; a<M; a++){//calcolo degli integrali con uniform sampling
        I[a] = 0;
        integral.UniformSampling(L);
        I[a] = integral.GetI(); //calcolo dell'integrale
        integral.New();
        }

    MB.Analisi(I, "integrale.dat");

//#######################################################################
            
    for(int a=0; a<M; a++){ //calcolo degli integrali con uniform sampling
        I[a] = 0;
        integral.ImportanceSampling(L);
        I[a] = integral.GetI(); //calcolo dell'integrale
        integral.New();
        }
    
    MB.Analisi(I, "integrale2.dat");
    
	return 0;

}	



