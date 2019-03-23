CC = g++

polynomials: main.o polynomial.o monomial.o
	$(CC) -Wall main.o polynomial.o monomial.o -o polynomials

main.o: main.cpp
	$(CC) -c main.cpp

polynomial.o: polynomial.cpp
	$(CC) -c polynomial.cpp

monomial.o: monomial.cpp
	$(CC) -c monomial.cpp

