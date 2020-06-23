CC = g++
CFLAGS = -Wall -O3 --std=c++11

MolDyn_NVE.exe : metBlocchi.o MolDyn_NVE.o 
	$(CC) metBlocchi.o MolDyn_NVE.o -o MolDyn_NVE.exe
MolDyn_NVE.o : MolDyn_NVE.cpp
	$(CC) -c MolDyn_NVE.cpp -o MolDyn_NVE.o $(CFLAGS)
metBlocchi.o : metBlocchi.cpp
	$(CC) -c metBlocchi.cpp -o metBlocchi.o $(CFLAGS)

clean :
	rm *.o MolDyn_NVE.exe
