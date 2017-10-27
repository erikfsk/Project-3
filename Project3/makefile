compile= c++ 
LIB=  -larmadillo


#standard.exe	:	standard.cpp
#	${compile} -o standard.exe standard.cpp


solsys.exe	:	planet.o  main.o solarsystem.o
	${compile} -o solsys.exe planet.o main.o solarsystem.o 


planet.o	:	planet.cpp
	${compile} -c  planet.cpp


main.o	:	main.cpp
	${compile} ${LIB} -c  main.cpp


solarsystem.o	:	solarsystem.cpp
	${compile} ${LIB} -c  solarsystem.cpp


