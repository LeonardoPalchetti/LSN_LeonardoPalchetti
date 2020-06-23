CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe :  random.o esperimento.o metBlocchi.o main.o
	$(CC) random.o esperimento.o metBlocchi.o main.o -o main.exe
main.o : main.cpp 
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
esperimento.o : esperimento.cpp esperimento.h
	$(CC) -c esperimento.cpp -o esperimento.o $(CFLAGS)
metBlocchi.o : metBlocchi.cpp metBlocchi.h
	$(CC) -c metBlocchi.cpp -o metBlocchi.o $(CFLAGS)
clean :
	rm *.o main.exe

	
