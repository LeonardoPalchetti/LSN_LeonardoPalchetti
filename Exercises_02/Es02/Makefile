CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o random.o randomwalk.o 
	$(CC)  randomwalk.o random.o main.o -o main.exe
main.o : main.cpp 
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
randomwalk.o : randomwalk.cpp randomwalk.h
	$(CC) -c randomwalk.cpp -o randomwalk.o $(CFLAGS)
clean :
	rm *.o main.exe
