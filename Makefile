# Makefile for Bank Management System
# Usage:
#   make        -> builds the main app
#   make test   -> builds and runs tests
#   make clean  -> removes compiled files

CXX    = g++
CFLAGS = -Wall -std=c++11

all: bank_app

bank_app: bank_management.cpp
	$(CXX) $(CFLAGS) -o bank_app bank_management.cpp

test: test_bank_management.cpp
	$(CXX) $(CFLAGS) -o test_bank_management test_bank_management.cpp
	./test_bank_management

clean:
	rm -f bank_app test_bank_management
