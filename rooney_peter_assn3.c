/*
Author: Peter Rooney 
Date: 10/29/23
Description: This provides the main method that takes in and checks the 
command line arguments to run rotorMachine.c 
Usage: 
 ./exe -i <file>
     ./exe -e <file1> <file2> -r <r1> <r2>
     ./exe -d <file1> <file2> -r <r1> <r2>
     ./exe -e <file1> <file2> -r <r1> <r2> -i <file>
     ./exe -d <file1> <file2> -r <r1> <r2> -i <file>
*/

#include<stdio.h>
#include"rotorMachine.h"
#include<string.h>
#include<stdlib.h>

int main( int argc, char* argv[])
{
  printf("argc = %d\n", argc);
  for ( int i =0; i< argc; i++)
   {
     printf("argc[%d] = %s\n", i, argv[i]);
   }
  char *filename= NULL;
  if(argc < 2) // if there isonly one argument exit program 
    {
      printUsage(); 
    }
  if (argc ==9 && strcmp(argv[1],"-e")==0 && strcmp(argv[7],"-i")) // checks for  ./exe -e <file1> <file2> -r <r1> <r2> -i <file>                                                            
    {
      filename =argv[8];
      buildIni(filename);
      int rotor1[28];
      int rotor2[28];
      buildRotors( rotor1, rotor2);
      setRotor1(rotor1,atoi(argv[5]));
      setRotor2(rotor2,atoi(argv[6]));
      FILE* infile = fopen(argv[2], "r");
      FILE* outfile =fopen(argv[3], "w");
      encryptFile(infile, outfile, rotor1, rotor2);
      fclose(infile);
      fclose(outfile);
      return 0; 
    }
  else if (argc ==9 && strcmp(argv[1],"-d")==0 && strcmp(argv[7],"-i")) //  ./exe -d <file1> <file2> -r <r1> <r2> -i <file>                                                                       
    {
      filename =argv[8];
      buildIni(filename);
      int rotor1[28];
      int rotor2[28];
      buildRotors( rotor1, rotor2);
      setRotor1(rotor1,atoi(argv[5]));
      setRotor2(rotor2,atoi(argv[6]));
      FILE* infile = fopen(argv[2], "r");
      FILE* outfile =fopen(argv[3], "w");
      decryptFile(infile, outfile, rotor1, rotor2);
      return 0; 
    }  

  if (argc ==3 && strcmp(argv[1],"-i") ==0) // checks for  ./exe -i <file>   
    {
      filename = argv[2];
      buildIni(filename);
    }
  if (argc ==7 && strcmp(argv[1],"-e")==0) // checks for  ./exe -e <file1> <file2> -r <r1> <r2>                     
    {
      //set up the numbers to be used for rotor.ini
      //    buildIni(filename);
      // create the rotor arrays 
      int rotor1[28];
      int rotor2[28];
      // build rotors 
      buildRotors( rotor1, rotor2);
      // set to corrisponding rotations given in the command line argumet 
      // must change from string to int
      setRotor1(rotor1, atoi(argv[5]));
      setRotor2(rotor2, atoi(argv[6]));
      // set the infile and outfile to what was given in the command line 
      FILE* infile = fopen(argv[2], "r");
      FILE* outfile = fopen(argv[3], "w");
      //run the encrypt file 
      encryptFile(infile, outfile, rotor1, rotor2);
  
      // implememntation is similar for the rest of the cases - except decrpyt and encrypt and the initialization files 
    }
  else if (argc ==7 && strcmp(argv[1],"-d")==0) // checks for  ./exe -d <file1> <file2> -r <r1> <r2>                     
    {
      // buildIni(filename);
      int rotor1[28];
      int rotor2[28];
      buildRotors( rotor1, rotor2);
      setRotor1(rotor1, atoi(argv[5]));
      setRotor2(rotor2,atoi(argv[6]));
      FILE* infile = fopen(argv[2], "r");
      FILE* outfile =fopen(argv[3], "w");
      decryptFile(infile, outfile, rotor1, rotor2);  //decrpytt
    }
  else // if none of these are met print the usage message 
    {
      printUsage();
       
    }
  return 0; 
}

/*
Method that prints out the usage message
 */
void printUsage()
{
  printf("\nusage\n"
     "./exe -i <file>\n>"
     "./exe -e <file1> <file2> -r <r1> <r2>\n"
     "./exe -d <file1> <file2> -r <r1> <r2>\n"
     "./exe -e <file1> <file2> -r <r1> <r2> -i <file>\n"
     "./exe -d <file1> <file2> -r <r1> <r2> -i <file>");
}
