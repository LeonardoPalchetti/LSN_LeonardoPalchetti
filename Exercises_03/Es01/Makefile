CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o random.o blackscholes.o metBlocchi.o
	$(CC) metBlocchi.o blackscholes.o random.o main.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
blackscholes.o : blackscholes.cpp blackscholes.h
	$(CC) -c blackscholes.cpp -o blackscholes.o $(CFLAGS)
metBlocchi.o : metBlocchi.cpp metBlocchi.h
	$(CC) -c metBlocchi.cpp -o metBlocchi.o $(CFLAGS)
clean :
	rm *.o main.exe
