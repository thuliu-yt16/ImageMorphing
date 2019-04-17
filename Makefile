all: main.exe

main.exe: main.o graph.o point.o vector3.o image.o triangle.o
	g++ -o main.exe main.o graph.o point.o vector3.o image.o triangle.o -O2 -std=c++11

graph.o: graph.cpp graph.h defs.h
	g++ -c graph.cpp -O2 -std=c++11

point.o: point.cpp point.h defs.h
	g++ -c point.cpp -O2 -std=c++11

vector3.o: vector3.h vector3.cpp defs.h
	g++ -c vector3.cpp -O2 -std=c++11

image.o: image.h image.cpp defs.h
	g++ -c image.cpp -O2 -std=c++11

main.o: main.cpp defs.h
	g++ -c main.cpp -O2 -std=c++11

triangle.o: triangle.h triangle.cpp
	g++ -c triangle.cpp -O2 -std=c++11

clean:
	rm *.o

run: main.exe
	./main.exe
