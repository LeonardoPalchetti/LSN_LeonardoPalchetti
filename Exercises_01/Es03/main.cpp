#include <iostream>
#include "random.h"
#include "esperimento.h"
#include "metBlocchi.h"
#include <fstream>
#include <cmath>


using namespace std;


int main(){

    double D = 0.1;  //Distanza fra le linee (lavoro in un foglio 1x1, righe verticali)
    double L = 0.07; //Lunghezza ago
    int T= 3000000;    //numero di lanci
    int M = 100, E=T/M;    //numero di blocchi , numero lanci in ogni blocco
    double pi[M]; //:= array PI esperimento
    
    Esperimento esp;
    MetBlocchi MB(M);
    
    esp.SetD (D);
    esp.SetL(L);
    
    for(int a = 0; a < M; a++){     //eseguo l'esperimento per ogni blocco
        for (int j = 0; j<E; j++)
            esp.Esegui();
        
        esp.Analisi(E);
        
        pi[a] = esp.PI(); //misura di PI
        //pi2[a] = pi[a]*pi[a]; //misura di PI^2
        
        esp.New();
    }
            
    MB.Analisi(pi, "misurePI.dat");
   
	return 0;

}	


    
