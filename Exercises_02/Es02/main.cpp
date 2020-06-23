#include <iostream>
#include "randomwalk.h"
#include "random.h"


using namespace std;

double error (double, double, int);//funzione calcolo errore Metodo Blocchi

int main(){

    int T = 10000; //numero randomwalk totali
    int M = 100; //numero di blocchi
    int E = T/M; //numero di randomwalk in ogni blocco
    int P = 101; //numero di passi randomwalk (devo tenere conto anche del'origine

    //randomwalk lattice
    double d[P][M], d2[P][M]; //vettore delle distanze e delle distanze al quadrato (passo)(blocco)
    double prog_d[P][M]; //vettore medie progressive
    double prog_d2[P][M]; //vettore medie^2 progressive
    double err_d[P][M]; //vettore errori
    
    //randowalk space
    double D[P][M], D2[P][M];//vettore delle distanze e delle distanze al quadrato (passo)(blocco)
    double prog_D[P][M]; //vettore medie progressive
    double prog_D2[P][M]; //vettore medie^2 progressive
    double err_D[P][M]; //vettore errori
    
    fstream output;
    RandomWalk rndwalk(P);

    for (int a = 0; a < M; a++){ //Genero Randomwalk sul reticolo e calcolo la distanza dall'origine ad ogni step.
        
        for(int j = 0; j<P; j ++)
                d[j][a] = 0;   //Sono sicuro di partire da zero nella somma

        for(int i = 0; i< E; i++){      //eseguo E randomwalk per blocco
            
            rndwalk.Passo_lattice(); //esegui il randomwalk
            rndwalk.AnalisiDist();  //eseguo analisi distanze

            for(int j = 0; j<P; j ++)
                d[j][a] += rndwalk.GetDist(j);     //Sommo tutte le distanze per blocco
                
            rndwalk.New();
        }
        
        for(int j = 0; j<P; j ++){
            d[j][a] = sqrt(d[j][a]/E);  //media per ogni blocco
            d2[j][a] = d[j][a]*d[j][a]; //media quadra
        }
    }
    

    for(int a =0; a< M; a++){   //statistiche sui blocchi
        for(int j = 0; j<P; j ++){
            prog_d[j][a] = 0;
            prog_d2[j][a] = 0;
        } //Sono sicuro di partire da zero nella somma
        
        for(int i=0; i<a+1; i++){
            for(int j=0; j<P; j++){
                prog_d[j][a] += d[j][i];
                prog_d2[j][a] += d2[j][i];
            }
        }
        
    for(int j=0; j<P; j++){ 
                prog_d[j][a] /=(a+1);
                prog_d2[j][a] /=(a+1);
                err_d[j][a] = error(prog_d[j][a], prog_d2[j][a], a);
            }
    }
    
    output.open("randomwalk.dat", ios::out);        //carico su file solo i risultati dell'ultimo blocco
    for(int j=0; j<P; j++)
        output << prog_d[j][M-1] << " " << err_d[j][M-1] << endl;
    output.close();        
    output.open("finalDist.dat", ios::out);        //carico su file solo i risultati dell'ultimo blocco
    for(int j=0; j<M; j++)
        output << prog_d[P-1][j] << " " << err_d[P-1][j] << endl;
    output.close(); 
//############################## RANDOMWALK NELLO SPAZIO ########################################// 


    for (int a = 0; a < M; a++){    //Genero Randomwalk sullo spazio e calcolo la distanza dall'origine ad ogni step.
        
        for(int j = 0; j<P; j ++)
                D[j][a] = 0;   //Sono sicuro di partire da zero nella somma
                
                
        for(int i = 0; i< E; i++){      //eseguo E randomwalk per blocco
            
            rndwalk.Passo_space(); //esegui il randomwalk
            rndwalk.AnalisiDist();  //eseguo analisi distanze
            
            
            
            for(int j = 0; j<P; j ++)
                D[j][a] += rndwalk.GetDist(j);     //Sommo tutte le distanze per blocco
                
            rndwalk.New();
        }
        
        for(int j = 0; j<P; j ++){
            D[j][a] = sqrt(D[j][a]/E);  //media per ogni blocco
            D2[j][a] = D[j][a]*D[j][a]; //media quadrata della distanza per ogni blocco
        }
    }
    

    for(int a =0; a< M; a++){ //statistiche sui blocchi
        for(int j = 0; j<P; j ++){
                prog_D[j][a] = 0;
                prog_D2[j][a] = 0;
        } //Sono sicuro di partire da zero nella somma
        
        for(int i=0; i<a+1; i++){
            for(int j=0; j<P; j++){
                prog_D[j][a] += D[j][i];
                prog_D2[j][a] += D2[j][i];
            }
        }
        
        for(int j=0; j<P; j++){
                prog_D[j][a] /=(a+1);
                prog_D2[j][a] /=(a+1);
                err_D[j][a] = error(prog_D[j][a], prog_D2[j][a], a);
            }
    }
    
    output.open("randomwalk2.dat", ios::out);        //carico su file solo i risultati dell'ultimo blocco
    for(int j=0; j<P; j++)
        output << prog_D[j][M-1] << " " << err_D[j][M-1] << endl;
    output.close();
    output.open("finalDist2.dat", ios::out);        //carico su file solo i risultati dell'ultimo blocco
    for(int j=0; j<M; j++)
        output << prog_D[P-1][j] << " " << err_D[P-1][j] << endl;
    output.close(); 
	return 0;

}	

double error (double av, double av2, int n){
    if (n==0)
        return 0;
    else
        return sqrt((av2 - av*av)/n);
};

