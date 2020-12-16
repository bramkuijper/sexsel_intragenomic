# makefile to compile the
# individual based simulation into
# a runnable executable file

EXE=sexsel_intragenomic.exe
CPP=sexsel_intragenomic.cpp individual.cpp patch.cpp
HPP=individual.hpp patch.hpp
LIBS=yaml-cpp


all : $(EXE)


$(EXE): $(CPP) $(HPP)
	g++ -ggdb -std=c++17 -Wall -O3 -o $@ $(CPP) -l$(LIBS)

.PHONY :
	clean

clean :
	rm -rf $(EXE)
