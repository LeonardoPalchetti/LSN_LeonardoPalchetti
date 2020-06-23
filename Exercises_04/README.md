In questa cartella sono presenti:

    * jupyter dell'esercitazione, con analisi dei dati trovati.
    
    * Es01, svolgimento dell'esercitazione 4.1 con:
        
        - Makefile
        - MolDyn_NVE.cpp e .h 
        - file input.solid/.liquid/.gas/.dat: hanno i parametri iniziali per i vari stati.
        - file config.fcc/.0/.final: hanno informazioni sulle configurazioni spaziali del reticolo fcc, della configurazione iniziale e finale
        - file old.0/old.final: configurazione al penultimo step, serve per la funzione Restart()
        
        - file dei risultati: per ogni fase c'è un file con nomefase_misura.dat (anche nomefase2_misura.dat).  Sono le misure di Enegia Totale, Potenziale, Cinetica e della Temperatura per ogni fase. Quelli indicizzati con il 2 sono le misure per la long-simulation, le altre sono per la multi-short simulation. (spiego nel jupiter)
        

    * Es02, svolgimento dell'esercitazione 4.2 e 4.3 con:
        
        - Makefile
        - MolDyn_NVE.cpp e .h 
        - classe metBlocchi: serve per svolgere l'analisi con il metodo a blocchi
        - file input.solid/.liquid/.gas/.dat: hanno i parametri iniziali per i vari stati.
        - file config.fcc/.0/.final: hanno informazioni sulle configurazioni spaziali del reticolo fcc, della configurazione iniziale e finale
        - file old.0/old.final: configurazione al penultimo step, serve per la funzione Restart()
        - script run.sh e run2.sh mi sono serviti per far andare il codice in maniera automatica. (dovevo equilibrare prima di prendere le misure).
        
        - file dei risultati: per ogni fase c'è un file con nomefase_misura.dat.  Sono le misure di Enegia Totale, Potenziale, Cinetica e della Temperatura per ogni fase.
