COMPILER=g++
FLAGS=-std=c++14 -pedantic -Wall

all: main

main: $(wildcard *.cpp) $(wildcard *.h) $(wildcard */*.cpp) $(wildcard */*.h)
	$(COMPILER) $(FLAGS) $(wildcard *.cpp) $(wildcard */*.cpp) -o d6r -lpcap -pthread

clean:
	rm -rf d6r