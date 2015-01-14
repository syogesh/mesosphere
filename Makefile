CC = g++
LD = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall

.PHONY = run

all: Simulator

Simulator: Simulator.cpp Node.cpp Job.cpp
	$(CC) $(CFLAGS) -o $@ $^

run: Simulator
	./Simulator < input

clean:
	rm -f *.o
