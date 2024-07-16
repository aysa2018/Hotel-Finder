# The target executable name
hotelFinder: main.o  hashtable.o  hotel.o  
	g++ main.o hashtable.o hotel.o -o hotelFinder 

# Compilation rules for each source file
main.o: main.cpp 
	g++ -c main.cpp

hashtable.o: hashtable.cpp hashtable.h bst.hpp 
	g++ -c hashtable.cpp

hotel.o: hotel.cpp hotel.h
	g++ -c hotel.cpp

# Clean rule to remove object files and the executable
clean:
	rm bst.o hotel.o hashtable.o main.o
