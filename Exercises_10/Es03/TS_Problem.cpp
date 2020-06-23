#include "mpi.h"
#include <stdlib.h>
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "random.h" //generatore random
#include "population.h"


using namespace std;

int main(int argc, char* argv[]){
    
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status stat1, stat2; //forse da cambiare

    //variabili e classi
    int n_cities = 32;    //numero città
    int icity;
    int time = 50000;
    int migr = 50;
    int n_time = time/migr;
    
    int *recive;
    
    int* imesg1 = new int[n_cities]; int* imesg2 = new int[n_cities];
    int* imesg3 = new int[n_cities]; int* imesg4 = new int[n_cities];
    int itag=1; int itag2=1;

    int * nodo = new int[size];
    
    
    fstream output;
    Population percorso(100,n_cities, rank); //popolazione
    Random rnd;
    
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
    
//################ Codice ###########
    
    cout << "Il numero di città da visitare è : " <<  n_cities << " per il nodo " << rank << endl;
    

    recive = new int[n_cities];
    
    output.open("lunghezze_" + to_string(rank) + ".dat", ios::out);
    //eseguo ottimizzazione
    for(int imig= 0; imig<= migr; imig++){
        for(int itime = 0; itime < n_time; itime++){
            percorso.Evoluzione();
            output << percorso.GetLunghezza(0) << endl;
        }
        if(imig != migr){
            if(rank ==0){
                for(int i = 0; i < size; i++) nodo[i] = 0;
    
                int a;
                int b, c;
    
                for(int i = 0; i < size; i++){
                    a = i;
                    b = 0;
                    do{
                        c = rnd.Rannyu()*(size);
                        if(nodo[c] == 0){
                            nodo[c] = a;
                            b = 1;
                        }
                    }while(b == 0);
                }
            }
        
            //distribuisco su tutti i nodi
            MPI_Bcast(&nodo[0], size, MPI_INT, 0, MPI_COMM_WORLD);
        
            percorso.Ordina(); //sono sicuro di aver ordinato la popolazione
        
            if(rank == nodo[0]){
                        
                for(int i =0; i < n_cities; i++) imesg1[i] = percorso.Invia(i);
            
                MPI_Send(&imesg1[0], n_cities, MPI_INT, nodo[1], itag, MPI_COMM_WORLD);
                MPI_Recv(&imesg2[0], n_cities, MPI_INT, nodo[1], itag, MPI_COMM_WORLD,&stat1);
                for(int i =0; i < n_cities; i++) recive[i] = imesg2[i] ;
            }
        
            if(rank == nodo[1]){
                for(int i =0; i < n_cities; i++) imesg2[i] = percorso.Invia(i);
           
                MPI_Send(&imesg2[0], n_cities, MPI_INT, nodo[0], itag, MPI_COMM_WORLD);
                MPI_Recv(&imesg1[0], n_cities, MPI_INT, nodo[0], itag, MPI_COMM_WORLD,&stat1);
            
                for(int i =0; i < n_cities; i++) recive[i] = imesg1[i] ;
            }
        
            if(rank == nodo[2]){
            
                for(int i =0; i < n_cities; i++) imesg3[i] = percorso.Invia(i);
            
                MPI_Send(&imesg3[0], n_cities, MPI_INT, nodo[3], itag2, MPI_COMM_WORLD);
                MPI_Recv(&imesg4[0], n_cities, MPI_INT, nodo[3], itag2, MPI_COMM_WORLD,&stat2);
                for(int i =0; i < n_cities; i++) recive[i] = imesg4[i] ;
            
            }
        
            if(rank == nodo[3]){
            
                for(int i =0; i < n_cities; i++) imesg4[i] = percorso.Invia(i);
            
                MPI_Send(&imesg4[0], n_cities, MPI_INT, nodo[2], itag2, MPI_COMM_WORLD);
                MPI_Recv(&imesg3[0], n_cities, MPI_INT, nodo[2], itag2, MPI_COMM_WORLD,&stat2);
            
                for(int i =0; i < n_cities; i++) recive[i] = imesg3[i] ;
            }
    
            percorso.Scambia(recive);
        }
    }

    output.close();
    
    
    percorso.GetSolution();
    
    output.open("mappa_" + to_string(rank) + ".dat", ios::out);
   for(icity = 0; icity < n_cities; icity ++) output << icity + 1 << "   " << percorso.GetX(icity) << "   " << percorso.GetY(icity) << "   " << percorso.GetName(icity) << endl;
   output << 1 << "   " << percorso.GetX(0) << "   " << percorso.GetY(0) << "   " << percorso.GetName(0) << endl;
    output.close();
    
   
 
    cout << "Il percorso più breve è lungo L =  " <<  percorso.GetLunghezza(0) << "per il nodo " << rank << endl;
    
    percorso.Delete();
    
    delete [] recive;
    
    MPI_Finalize();
    return 0;
}
    



    
    
    
