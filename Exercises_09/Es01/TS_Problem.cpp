#include <stdlib.h>
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "random.h" //generatore random
#include "population.h"

using namespace std;

int main(){
    
    //variabili e classi
    int n_cities = 32;    //numero città
    int icity;
    int time = 20000;
    
    fstream output, output2;
    Population percorso(100,n_cities); //popolazione
    
//################ Codice ###########
    
    cout << "Il numero di città da visitare è : " <<  n_cities << endl;
    
    output.open("lunghezze.dat", ios::out);
    output2.open("mediaL.dat", ios::out);
    //eseguo ottimizzazione
    for(int itime = 0; itime < time; itime++){
        percorso.Evoluzione();
        output << itime << "   " << percorso.GetLunghezza(0) << endl;
        output2 << itime << "   " << percorso.BestMedia() << endl;
    }
    output.close();
    output2.close();
    
    cout << "Ho eseguito l'ottimizzazione" << endl;
    //stampo soluzione su file
    
    percorso.GetSolution();
    
    output.open("mappa.dat", ios::out);
   for(icity = 0; icity < n_cities; icity ++) output << icity + 1 << "   " << percorso.GetX(icity) << "   " << percorso.GetY(icity) << "   " << percorso.GetName(icity) << endl;
   output << 1 << "   " << percorso.GetX(0) << "   " << percorso.GetY(0) << "   " << percorso.GetName(0) << endl;
    output.close();
    
    
    cout << "Il percorso più breve è lungo L =  " <<  percorso.GetLunghezza(0) << endl;
    
    percorso.Delete();
    
    return 0;
}
    



    
    
    
