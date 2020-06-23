#include "metBlocchi.h"

using namespace std;

MetBlocchi :: MetBlocchi(int M):
   _M(M){};
    
MetBlocchi :: ~MetBlocchi(){};


void MetBlocchi :: Analisi(double m[] , string nomefile){
    fstream risultati;
    
    _m2 = new double[_M];
    
    for(int i=0; i<_M; i++)
        _m2[i] = m[i]*m[i];
    
    _prog_m = new double [_M];
    _prog_m2 = new double [_M];
    _err_m = new double [_M];
    
    for(int i=0; i<_M; i++){     //carico i file su dati
        _prog_m[i] = 0;
        _prog_m2[i] = 0;
        _err_m[i] = 0;
        }
    
    risultati.open(nomefile, ios::out);   
    for(int i=0; i<_M; i++){     //carico i file su dati
        for(int j=0; j<i+1; j++){
                    _prog_m[i]+=m[j];
                    _prog_m2[i]+= _m2[j];
        }
    
        _prog_m[i]/=(i+1);
        _prog_m2[i]/=(i+1);        
        _err_m[i] = error(_prog_m[i], _prog_m2[i], i);
        risultati << _prog_m[i] << " " << _err_m[i] << endl;
    }
   risultati.close();
   

};

double MetBlocchi :: error (double av, double av2, int n){
    if (n == 0)
        return 0;
    else
        return sqrt((av2 - av*av)/n);
};
    
        
