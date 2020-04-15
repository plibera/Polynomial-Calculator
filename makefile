CC = g++

polynomials: main.o polynomial.o monomial.o tests.o
	$(CC) -Wall main.o polynomial.o monomial.o tests.o -o polynomials
	rm main.o polynomial.o monomial.o tests.o

main.o: main.cpp
	$(CC) -c main.cpp

polynomial.o: polynomial.cpp
	$(CC) -c polynomial.cpp

monomial.o: monomial.cpp
	$(CC) -c monomial.cpp

tests.o: tests.cpp
	$(CC) -c tests.cpp
