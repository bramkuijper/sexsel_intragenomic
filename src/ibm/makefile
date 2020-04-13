# makefile to compile the
# individual based simulation into
# a runnable executable file

EXE=sexsel_intragenomic.exe

CPP=sexsel_intragenomic.cpp



all : $(EXE)


$(EXE): $(CPP)
	g++ -std=c++11 -Wall -O3 -o $(EXE) $(CPP)


.PHONY :
	clean

clean :
	rm -rf $(EXE)
