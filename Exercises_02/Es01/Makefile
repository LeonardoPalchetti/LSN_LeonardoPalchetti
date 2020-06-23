CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o random.o integrale.o metBlocchi.o
	$(CC) metBlocchi.o integrale.o random.o main.o -o main.exe
main.o : main.cpp 
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
integrale.o : integrale.cpp integrale.h
	$(CC) -c integrale.cpp -o integrale.o $(CFLAGS)
metBlocchi.o : metBlocchi.cpp metBlocchi.h
	$(CC) -c metBlocchi.cpp -o metBlocchi.o $(CFLAGS)
clean :
	rm *.o main.exe
