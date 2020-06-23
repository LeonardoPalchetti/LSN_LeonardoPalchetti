#include <stdlib.h>
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "random.h" //generatore random
#include "simulatedAnnealing.h"

using namespace std;

int main(){
    
    //variabili e classi
    int n_cities = 32;    //numero città
    int icity;
    int n_beta = 15; //numero di temperature
    int n_time = 10000; //numero di evoluzioni ad una certa temperatura
    
    fstream output;
    SimulatedAnnealing percorso(n_cities); //popolazione
    
//################ Codice ###########
    
    cout << "Il numero di città da visitare è : " <<  n_cities << endl;
    
    output.open("lunghezze.dat", ios::out);
    //eseguo ottimizzazione
    for(int ibeta = 0; ibeta < n_beta; ibeta++){
        output << n_time*(ibeta) << "   " << percorso.GetL() << endl;
        for(int itime = 0; itime < n_time; itime++){
            percorso.Evoluzione();
        }
        
        percorso.Tempering(); //cambio la temperatura
    }
    
    output.close();
    
    cout << "Ho eseguito l'ottimizzazione" << endl;
    //stampo soluzione su file
    
    output.open("mappa.dat", ios::out);
    for(icity = 0; icity < n_cities; icity ++) output << icity + 1 << "   " << percorso.GetX(icity) << "   " << percorso.GetY(icity) << "   " << percorso.GetName(icity) << endl;
    output << 1 << "   " << percorso.GetX(0) << "   " << percorso.GetY(0) << "   " << percorso.GetName(0) << endl;
    output.close();
    
    
    cout << "Il percorso più breve è lungo L =  " <<  percorso.GetL() << endl;
    
    percorso.Delete();
    
    return 0;
}
    



    
    
    
