# Author: Brack Harmon

#variables for compiler and compiler flags
CC = g++
CFLAGS = -Wall -pthread

#target to be built
all: clean load_balancer run
load_balancer: main.o
	$(CC) $(CFLAGS) -o load_balancer main.o

#auto run the executable
run: 
	./load_balancer

# #rules to build main.o file
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

#cleans executable and object files
clean:
	rm -f load_balancer *.o