CC = g++
CFLAGS = -Wall -O3 --std=c++11

TS_Problem.exe : TS_Problem.o random.o  population.o
	mpicxx population.o  random.o TS_Problem.o -o TS_Problem.exe
TS_Problem.o : TS_Problem.cpp 
	mpicxx -c TS_Problem.cpp -o TS_Problem.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
population.o : population.cpp population.h
	$(CC) -c population.cpp -o population.o $(CFLAGS)
clean :
	rm *.o TS_Problem.exe
