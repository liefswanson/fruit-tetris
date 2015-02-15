libs = -lGLEW -lglfw -lGL -lX11 -lpthread #-lXrandr -lXi
flags = -Wall -g
std = -std=c++11
cc = clang++
exe = fruit-tetris

all: main.o tile.o shader.o
	$(cc) $(std) $(libs) main.o tile.o shader.o -o $(exe).exe

main.o: main.cpp
	$(cc) $(std) $(flags) -c main.cpp -o main.o

tile.o: tile.cpp 
	$(cc) $(std) $(flags) -c tile.cpp  -o tile.o

shader.o: shader.cpp
	$(cc) $(std) $(flags) -c shader.cpp -o shader.o

rangeMap.o: rangeMap.cpp 
	$(cc) $(std) $(flags) -c rangeMap.cpp -o rangeMap.o

test: rangeMapTest

rangeMapTest: rangeMap.o tests/rangeMapTest.cpp
	$(cc) $(std) $(flags) rangeMap.o tests/rangeMapTest.cpp -o tests/rangeMapTest.exe
	tests/rangeMapTest.exe

prun: all
	primusrun ./$(exe).exe

run: all
	./$(exe).exe

clean:
	rm *.o *.exe
	rm tests/*.o tests/*.exe
