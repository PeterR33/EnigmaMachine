exe: rooney_peter_assn3.o rotorMachine.o
	gcc -g -Wall rooney_peter_assn3.o rotorMachine.o -o exe

rooney_peter_assn3.o: rotorMachine.h
	gcc -g -Wall -c rooney_peter_assn3.c rotorMachine.c 

rotorMachine.0: rotorMachine.h
	gcc -g -Wall -c rooney_peter_assn3.c rotorMachine.c

