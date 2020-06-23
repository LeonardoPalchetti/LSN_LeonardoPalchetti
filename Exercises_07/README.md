In questa cartella sono presenti:

    * jupyter dell'esercitazione, con analisi dei dati trovati.
    
    * Es01, svolgimento dell'esercitazione 7.1 con:
        
        - Makefile
        - Monte_Carlo_NVT.cpp e .h 
        - classe Random e file per la classe.
        - file input.solid/.liquid/.gas/.dat: hanno i parametri iniziali per i vari stati.
        - file config.fcc/.0/.final: hanno informazioni sulle configurazioni spaziali del reticolo fcc, della configurazione iniziale e finale.
        - script run.sh  mi sono serviti per far andare il codice in maniera automatica.        
        - file dei risultati: per ogni fase c'è un file con nomefase.misura.dat (anche nomefase_misura.dat per le misure instantanee) .  Sono le misure di Enegia Potenziale, Pressione, gdir (instantanea) e media per ogni fase.
        

    * Es02, svolgimento dell'esercitazione 7.2 con:
        
        - Makefile
        - Monte_Carlo_NVT.cpp e .h 
        - classe Random e file per la classe.
        - file input.solid/.liquid/.gas/.dat: hanno i parametri iniziali per i vari stati.
        - file config.fcc/.0/.final: hanno informazioni sulle configurazioni spaziali del reticolo fcc, della configurazione iniziale e finale
        - file old.0/old.final: configurazione al penultimo step, serve per la funzione Restart()
        - script run.sh  mi sono serviti per far andare il codice in maniera automatica.
        - file dei risultati: per ogni fase c'è un file con nomefase.misura.dat (anche nomefase_misura.dat per le misure instantanee) .  Sono le misure di Enegia Potenziale, Pressione, gdir (instantanea) e media per ogni fase.
        
    * Es03, confronto con algoritmo dinamica molecolare:
    
        - Makefile
        - MolDyn_NVE.cpp e .h 
        - classe metBlocchi: serve per svolgere l'analisi con il metodo a blocchi
        - file input.solid/.liquid/.gas/.dat: hanno i parametri iniziali per i vari stati.
        - file config.fcc/.0/.final: hanno informazioni sulle configurazioni spaziali del reticolo fcc, della configurazione iniziale e finale
        - file old.0/old.final: configurazione al penultimo step, serve per la funzione Restart()
        - script run.sh e runInitial.sh mi sono serviti per far andare il codice in maniera automatica. (dovevo equilibrare prima di prendere le misure).
        - file dei risultati: per ogni fase c'è un file con nomefase.misura.dat (anche nomefase_misura.dat per le misure instantanee) .  Sono le misure di Enegia Potenziale, Pressione, gdir (instantanea) e media per ogni fase.
