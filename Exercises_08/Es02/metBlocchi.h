#ifndef __MetBlocchi__
#define __MetBlocchi__

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>

class MetBlocchi {
    
protected:
    int _M;    //numero blocchi
    double *_m2; //:= array di m^2 esperimenti (con m misura esperimento)
    double *_prog_m, *_prog_m2, *_err_m; //:= array medie proggressive  blocchi, suo quadrato e errore
    
public:
    MetBlocchi(int);
    ~MetBlocchi();
    
    void Analisi(double [], std::string); //analisi media a blocchi, carica risultati su file.
    double error(double, double, int);	//funzione calcolo errore
    
};

#endif
