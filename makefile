CC = g++

polynomials: main.o polynomialClasses.o
	$(CC) main.o polynomialClasses.o -o polynomials

main.o: main.cpp
	$(CC) -c main.cpp

polynomialClasses.o: polynomialClasses.cpp
	$(CC) -c polynomialClasses.cpp
