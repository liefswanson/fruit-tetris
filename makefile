libs = -lGLEW -lglfw -lGL -lX11 -lpthread #-lXrandr -lXi
flags = -Wall -g
std = -std=c++11
cc = g++
exe = fruit-tetris

all: main.o tile.o shader.o rangeMap.o board.o block.o
	$(cc) $(std) $(libs) main.o tile.o shader.o rangeMap.o board.o block.o -o $(exe)

main.o: main.cpp
	$(cc) $(std) $(flags) -c main.cpp -o main.o

tile.o: tile.cpp 
	$(cc) $(std) $(flags) -c tile.cpp  -o tile.o

shader.o: shader.cpp
	$(cc) $(std) $(flags) -c shader.cpp -o shader.o

rangeMap.o: rangeMap.cpp 
	$(cc) $(std) $(flags) -c rangeMap.cpp -o rangeMap.o

board.o: board.cpp
	$(cc) $(std) $(flags) -c board.cpp -o board.o

block.o: block.cpp
	$(cc) $(std) $(flags) -c block.cpp -o block.o

run: all
	./$(exe)

clean:
	rm *.o *.exe
