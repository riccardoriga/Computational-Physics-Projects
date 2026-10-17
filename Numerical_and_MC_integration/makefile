LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

file : file.cpp Funzioni.h Integrali.h
	g++ -o file file.cpp ${INCS} ${LIBS}