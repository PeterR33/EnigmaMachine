#include<stdio.h>

void buildIni ();
int main (int argc, char** argv) 
{
  buildIni();
  return 0;
}

void buildIni()
{
  int SIZE =59;
  FILE *inFile, *outFile;   // creates infle and outfile pointers                            
  char inputBuffer[SIZE];
  //char outString [SIZE];
  // opend the in file to read                                                                              
  inFile= fopen ("config.rtr", "r");
  outFile = fopen ("rotors.ini" , "w");

  //Read each file of the line                                                                            
  int counter = 0;    // counts each line 
  int rotorNum ; // stores each rotor num found in the file
  int value; 
 
  while(fgets(inputBuffer, SIZE, inFile))  //  while its scans and there is an integer
    {
      if(fscanf(inFile, "%d\n", &rotorNum)==1)
	{
          value = rotorNum ^ 42;
          printf("%2d:  %d\n", counter, value);  // for debugging
      // write to the output file 
          fprintf(outFile, "%d\n", value);
	}
      else 
	{
	  printf( "Add these non ints to the list at line %d,: %s", counter, inputBuffer);
	  fprintf(outFile, "%s", inputBuffer);
	}
      counter ++;
    }
 }
