LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

file : file.cpp EquazioniDifferenziali.h VectorOperations.h
	g++ -o file file.cpp ${INCS} ${LIBS}