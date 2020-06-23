CC = g++
CFLAGS = -Wall -O3 --std=c++11

TS_Problem.exe : TS_Problem.o random.o  simulatedAnnealing.o 
	$(CC) simulatedAnnealing.o  random.o TS_Problem.o -o TS_Problem.exe
TS_Problem.o : TS_Problem.cpp 
	$(CC) -c TS_Problem.cpp -o TS_Problem.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
simulatedAnnealing.o : simulatedAnnealing.cpp simulatedAnnealing.h
	$(CC) -c simulatedAnnealing.cpp -o simulatedAnnealing.o $(CFLAGS)
clean :
	rm *.o TS_Problem.exe
