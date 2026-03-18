/*
Author: <Peter Rooney>
Date: 10/23/23
Description: This will have all the prototypes for the function 
to be implemented in the rotorMachine.c file
Usage: To define functions 
*/
#include<stdio.h>
#ifndef ROTORMACHINE_H
#define ROTORMACHINE_H


//Forward declaratoin - for all the method to be used in rootrMachine.c
// used to build the rotor.ini file that has the vlaues for the rotors
//Part A
void buildIni(char *);

//Part B
void buildRotors (int[28], int[28]);


//Part C
void rotateRotorRight(int [28]);
void rotateRotorLeft(int [28]);

void setRotor1(int [28], int);
void setRotor2(int [28], int);

//Part D
int  charToIndex(char);
char  indexToChar(int);

//Part F

void encryptFile(FILE*, FILE*, int rotor1[28], int rotor2[28]);
void decryptFile(FILE*,FILE*, int rotor1[28], int rotor2[28]);

char searchForIndex(int[28], int);
void printUsage();
#endif
