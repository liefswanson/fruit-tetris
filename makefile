libs = -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
flags = -Wall -g
std = -std=c++14
cc = clang++


all: main.o shader.o
	$(cc) $(std) $(libs) main.o shader.o -o main.exe

main.o: main.cpp
	$(cc) $(std) $(flags) -c main.cpp -o main.o

shader.o: shader.cpp
	$(cc) $(std) $(flags) -c shader.cpp -o shader.o

prun: all
	primusrun ./main.exe

run: all
	./main.exe

clean:
	rm *.o
