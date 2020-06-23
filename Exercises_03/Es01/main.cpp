#include <iostream>
#include "random.h"
#include "blackscholes.h"
#include <fstream>
#include <cmath>

using namespace std;

int main(){
    
    int N = 10000, M = 100; //numero di lanci, numero di blocchi
    int step = 100; //numero di passi per il calcolo progressivo
    
    //PARAMETERS
    int So = 100;
    double T = 1;
    int K = 100;
    double r = 0.1;
    double s = 0.25;
    
    BlackScholes bs(So, T, K, r, s);

     // Calcolo diretto
    bs.Diretto(N, M, "diretto");

    // Calcolo progressivo
    bs.Progressivo(N, M, step, "progressivo");
   
	return 0;

}	

