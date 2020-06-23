In questa cartella sono presenti:

    * jupyter dell'esercitazione, con analisi dei dati trovati.
    
    * Es01, svolgimento del The Traveling Salesman Problem nel caso di città sulla circonferenza:
        
        - Makefile
        - TS_Problem.cpp
        - classe Random e file per la classe
        - classe simulatedAnnealing: permette andare ad ottimizzare il miglior percorso rispetto ad una citta iniziale creata (sulla circonferenza). 
        - mappa.dat: contiene coordinate del percorso ottimizzato
        - lunghezze.dat: contiene misura lunghezza minima ad ogni evoluzione

        
    * Es02, svolgimento del The Traveling Salesman Problem nel caso di città all'interno di un quadrato
        
        - Makefile
        - TS_Problem.cpp
        - classe Random e file per la classe
        - classe simulatedAnnealing: permette andare ad ottimizzare il miglior percorso rispetto ad una citta iniziale creata (nel quadrato). 
        - mappa.dat: contiene coordinate del percorso ottimizzato
        - lunghezze.dat: contiene misura lunghezza minima ad ogni evoluzione
        
        
    * Es03, svolgimento del The Traveling Salesman Problem in parallelo
        
        - Makefile
        - TS_Problem.cpp
        - classe Random e file per la classe
        - classe popolazione: permette creare una popolazione di percorsi, con numero di città desiderato, in maniera da trovare il miglior percorso rispetto ad una citta iniziale creata (nel quadrato)). 
        - mappa_n.dat: contiene coordinate del percorso ottimizzato rispetto al nodo n (con n= 0,1,2,3)
        - lunghezze_n.dat: contiene misura lunghezza minima ad ogni evoluzione rispetto al nodo n (con n= 0,1,2,3)
