# makefile to compile the
# individual based simulation into
# a runnable executable file

EXE=sexsel_intragenomic.exe
CPP=sexsel_intragenomic.cpp individual.cpp main.cpp 
HPP=individual.hpp
LIBS=yaml-cpp


all : $(EXE)


$(EXE): $(CPP) $(HPP)
	g++ -ggdb -std=c++11 -Wall -O3 -o $@ $(CPP) -l$(LIBS)
#	g++ -std=c++11 -Wall -O3 -o $(EXE) $(CPP)


.PHONY :
	clean

clean :
	rm -rf $(EXE)
