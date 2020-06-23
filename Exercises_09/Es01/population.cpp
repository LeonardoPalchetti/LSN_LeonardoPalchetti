#include "population.h"

using namespace std;

Population :: Population(int CRO, int GEN) :   
   rnd(),
   n_cro(CRO),
   n_gen(GEN)
    {
      //parte di codice per la generazione numeri random
   	int seed[4]; //preparo il generatore di numeri random
   	int p1, p2;
   	ifstream Primes("Primes");
 	if (Primes.is_open()){
        //for(int i=0; i<3; i++)
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
  	 
    double x, y;
    
    map = new city[n_gen]; //il numero dei geni è uguale al numero delle città
    
    popolazione = new int* [n_cro]; 
    
    for(int icro = 0; icro < n_cro;  icro++) popolazione[icro] = new int[n_gen];
    
    lunghezza = new double[n_cro];
    
    for(int icity = 0; icity < n_gen; icity++){        
      x = rnd.Rannyu(-1,1);
      y = rnd.Rannyu(-1,1);
      
      if(y >= 0) y = sqrt(1-x*x);
      else y = -1*sqrt(1-x*x);
          
      map[icity].x = x;
      map[icity].y = y;
      map[icity].name = icity + 1;
    }
    
    BigBang(); //genera la prima popolazione
};

Population :: ~Population(){};



void Population :: BigBang(){
     
        
    for(int icro = 0; icro < n_cro; icro++)
            Permutazione(popolazione[icro]);
    
    Lunghezza();
    
    Ordina();
    
};
    
void Population :: Lunghezza(){
    
    double L;
    double dx = 0;
    double dy = 0;
    int pos1, pos2;
    
    for(int icro = 0; icro < n_cro; icro++){
        L = 0;
        for(int  icity = 0; icity < n_gen; icity++){
        
        if( icity != n_gen - 1){
            pos1 = popolazione[icro][icity] - 1; //il nome è posizione della mappa + 1;
            pos2 = popolazione[icro][icity + 1] - 1;
        
            dx = abs(map[pos1].x - map[pos2].x);
            dy = abs(map[pos1].y - map[pos2].y);
        
            L += sqrt(dx*dx + dy*dy);
        }
        
        else{
            pos1 = popolazione[icro][icity] - 1; //il nome è posizione della mappa + 1;
            pos2 = popolazione[icro][0] - 1;
            
            dx = abs(map[pos1].x - map[pos2].x);
            dy = abs(map[pos1].y - map[pos2].y);
        
            L +=  sqrt(dx*dx + dy*dy);
            }
        }
        lunghezza[icro] = L;
    }
};

void Population :: Ordina(){
    
    int min;
    double temp;
    int tempo[n_gen];
    
   for(int i=0; i<n_cro; i++){
        min = i;

    for(int j=i+1; j<n_cro; j++){
        if(lunghezza[j] < lunghezza[min]) min = j;
    }

        temp=lunghezza[min];
        lunghezza[min]=lunghezza[i];
        lunghezza[i]=temp;
    
        for(int k = 0; k < n_gen; k ++)tempo[k] = popolazione[min][k];
        for(int k = 0; k < n_gen; k ++)popolazione[min][k] = popolazione[i][k];
        for(int k = 0; k < n_gen; k ++)popolazione[i][k] = tempo[k];
    
    }
};

void Population :: Permutazione(int *percorso){
    
    percorso[0] = 1;
    
    for(int i = 1; i < n_gen; i++) percorso[i] = 0;
    
    int a;
    int b, c;
    
    for(int i = 1; i < n_gen; i++){
        a = i +1;
        b = 0;
        do{
            c = rnd.Rannyu()*(n_gen);
            if(percorso[c] == 0){
                percorso[c] = a;
                b = 1;
            }
        }while(b == 0);
    }
    
};

int Population :: RouletteTruccata(){
    
    double p[n_cro];
    double Ptot =0;
    double a; //per estrazione
    int i = 0; //indice estratto;
    double range = 0;
    
   
    for(int icro = 0; icro < n_cro; icro++){
        p[icro] = exp(-lunghezza[icro]);
        Ptot += p[icro];
    }

    a = rnd.Rannyu()*Ptot;
    for(int icro = 0; icro < n_cro; icro++){
        
        if( a >= range && a < (range + p[icro]))
            i = icro;
        
        range = range + p[icro];
        
    }
      
    return i;
};
    

void Population :: Evoluzione(){
    
    double scelta;
    int mut;
    int element;
    
    scelta = rnd.Rannyu();
    
   if(scelta < 0.7){
        Crossover();
    }
    
    mut = rnd.Rannyu()*(n_cro/4);
    
    for(int i=0; i<mut; i++){
        
        element = RouletteTruccata();
    
        Esegui(popolazione[element]);
    }
    
};


void Population :: Crossover(){


    int m, b; //indice mamma e babbo
    int taglio;
    int *figlio1, *figlio2;
    
    babbo = new int[n_gen];
    mamma = new int[n_gen];
    figlio1 = new int[n_gen];
    figlio2 = new int[n_gen];
    
    m = RouletteTruccata();
    
    do{
        b = RouletteTruccata();
    }while(m == b);
    
    taglio = rnd.Rannyu()*(n_gen - 1) + 1;
    
    
    //inizio a preparare genitori e figli
    for(int igen = 0; igen < n_gen; igen++){
        mamma[igen] = popolazione[m][igen];
        babbo[igen] = popolazione[b][igen];
        
        if(igen < taglio){
            figlio2[igen] = popolazione[m][igen];
            figlio1[igen] = popolazione[b][igen];
        }
        
        else{
            figlio2[igen] = 0;
            figlio1[igen] = 0;
        }
        
    }
    
    for(int i = 0; i < n_gen; i++){
        for(int j = 0; j < taglio; j++){
            if(babbo[i] == figlio2[j]) babbo[i] = 0;
            if(mamma[i] == figlio1[j]) mamma[i] = 0;
        }
    }
    
    for(int i = taglio; i < n_gen; i++){
        for(int j = 0; j < n_gen; j++){
            if(babbo[j] != 0){
                figlio2[i] = babbo[j];
                i = i + 1;
            }
        }
    }
                
    for(int i = taglio; i < n_gen; i++){
        for(int j = 0; j < n_gen; j++){
            if(mamma[j] != 0){
                figlio1[i] = mamma[j];
                i = i + 1;
            }
        }
    }
    
    Sostituisci(figlio1);
    Lunghezza();
    Ordina();
    Sostituisci(figlio2);
    Lunghezza();
    Ordina();
    
    delete [] mamma;
    delete [] babbo;
}    
    

void Population :: Esegui(int *percorso){
    
    double prob;
    
    int *copia;
    
    copia = new int[n_gen];
    
    for(int i =0; i< n_gen; i++) copia[i] = percorso[i];
    
   for(int i=0; i < 2; i++){
    prob = rnd.Rannyu();
    
    if( prob < 0.1) PairPermutation(copia);
    
    else if ( 0.4 <= prob && prob < 0.5 ) Shift(copia);
    
    else if ( 0.8 <= prob  && prob < 0.9)  BlockPermutation(copia);
    }
    Sostituisci(copia);
    Lunghezza();
    Ordina();
    
    
    delete [] copia;
    
};

void Population :: PairPermutation(int *nuovo){
    
    int a, b;
    int fake;
    
    a = rnd.Rannyu()*n_gen;
    if(a == 0) a = 1;
    
    do{
    b = rnd.Rannyu()*n_gen; 
    
    if(b == 0) b = 1;
    }while(b != a);
    
    fake = nuovo[a];
    nuovo[a] = nuovo[b];
    nuovo[b] = fake;
    
};

void Population :: Shift(int *nuovo){
    
    int a, b;
    
    int fake[n_gen];
    
    a = rnd.Rannyu()*(n_gen/2);
    
    fake[0] = nuovo[0];
    
    for (int i = 1; i < n_gen; i ++){
        
        b = a +i;
        if( b >= n_gen ) b = b  - (n_gen - 1);
        
        fake[b] = nuovo[i];
    }
    
    nuovo = fake;
   
};

void Population :: BlockPermutation(int *nuovo){
    
    int a, b,c;
    int d, e; //servono per le condizioni al contorno
    
    int fake;
    
    a = rnd.Rannyu()*n_gen; //scelgo un elemento da scambiare con il suo blocco
    if(a == 0) a = 1;
    
    c = rnd.Rannyu()*int(n_gen/2);
    c = c;
    
    do{
    b = rnd.Rannyu()*n_gen; 
    
    if(b == 0) b = 1;
    }while(abs(b - a) < c );
    
    for(int i=0; i < c; i++){
        
        d = a+i;
        if( d >= n_gen ) d = d  - (n_gen - 1);
        e = b+i;
        if( e >= n_gen ) e = e  - (n_gen - 1);
        
        
        fake = nuovo[d];
        nuovo[d] = nuovo[e];
        nuovo[e] = fake;
    }
   
};

void Population :: Sostituisci(int *nuovo){
    for(int igen = 0; igen < n_gen; igen++) popolazione[n_cro - 1][igen] = nuovo[igen];
};  
    
void Population :: GetSolution(){
    soluzione = new int[n_gen];
        
    for(int igen = 0; igen < n_gen; igen++) soluzione[igen] = popolazione[0][igen];
    
};

double Population :: GetX(int pos){
    
    int nome;
    
    nome = soluzione[pos];
    
    return map[nome - 1].x;
};
    
 double Population :: GetY(int pos){
    
    int nome;
    
    nome = soluzione[pos];
    
    return map[nome - 1].y;
}; 


int Population :: GetName(int pos){
    
    int nome;
    
    nome = soluzione[pos];
    
    return map[nome - 1].name;
}; 


double Population :: BestMedia(){
    
    double Lmedia = 0;
    
    double meta = n_cro*0.5;
    
    for(int i=0; i < meta; i++) Lmedia += lunghezza[i];
    
    return Lmedia/meta;
}
    

void Population :: Delete(){
    delete [] map;

    for(int icro = 0; icro < n_cro;  icro++) delete [] popolazione[icro];
    delete [] popolazione;
    delete [] lunghezza;

    delete [] soluzione;
};
    
    
    
    
    
