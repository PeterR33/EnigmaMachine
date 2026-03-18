/*
Author: Peter Rooney 
Date: 10/08/23
Description: This holds the implementations for the methods that create
the enigma Machine. There are two rotors that work togther to encrypt and decrypt messages  
Usage:   ./exe -i <file>
     ./exe -e <file1> <file2> -r <r1> <r2>
     ./exe -d <file1> <file2> -r <r1> <r2>
     ./exe -e <file1> <file2> -r <r1> <r2> -i <file>
     ./exe -d <file1> <file2> -r <r1> <r2> -i <file>
*/

#include<stdio.h>
#include"rotorMachine.h"
#include<ctype.h>
#include <string.h>


/* 
This Method takes in a file name and then reads 
values from that file and writes them to a file called rotor.ini
*/
void buildIni(char *filename)
{ 
  // first need to read the values from the config file                     
  //encrypt them with an XOR 42                                                
  //then wrrite them to a new file called 

  FILE *inFile, *outFile;   // creates infle and outfile pointers
  // open the infile to read and set the output
  inFile = fopen (filename, "r");
  outFile = fopen ("rotors.ini" , "w");

  //Read each file of the line
  int counter = 0; //to count each line - used for debuggin 
  int rotorNum  ; // used to get each values in the file
  int value; // the encrypted values with XOR 42
  while(fscanf(inFile, "%d\n", &rotorNum)==1) // while it scans it find an integer
    { 
      value = rotorNum ^ 42; // encryptes the value by XOR with 42
      //  printf("%2d:  %d\n", counter, value);  // for debugging
      counter ++; // for debugging
      // write to the output file
      fprintf(outFile, "%d\n", value); 
    }
  fclose(inFile);
  fclose(outFile);
}


/* 
This function takes two rotor arrays and populates them with the 
encrypted valeues from rotors.ini - indicating if that file DNE
*/
void buildRotors (int rotor1[28], int rotor2[28])
{
  FILE  *inFile;
  inFile = fopen("rotors.ini", "r");
  if (inFile == NULL)
    {
      printf("Error: Rotor machine not initialized.  Run with -i option and provide anappropriate configuration file.");
    }
  int rotorNums; // for each num in the rotor.ini file
  int encryptNum1; //encrypted number for rotor 1
  int encryptNum2;  // encrypted numbers for rotor 2
  int i ; // for loop
  for (i =0; i<56; i++)
    { 
      fscanf (inFile, "%d", &rotorNums);  //get each number in the file
      if (i>= 0 && i <28)  // the first 27 go into rotor 1
	{
        encryptNum1 = rotorNums ^ 42;
        rotor1[i] = encryptNum1;
	// printf("Rotor 1  Index: %d rotor 1 num: %d\n", i, rotor1[i]);
	}
      else if (i >=28 && i <56) // the second 27 go into rotor2
	{                   
	  encryptNum2 = rotorNums ^42;                                        
	  rotor2[i-28]= encryptNum2;    // make sure to start from index 1                   
	  //printf("Rotor 2 Index: %d rotor 2 num: %d\n",i-28, rotor2[i-28]); 
	}
    }
  fclose(inFile);
}


/*
This Function shifts all the elements in rotor one to the right 
where the last elements goes into the first posistion 
 */
void rotateRotorRight (int rotor[28])
{ 
  // printf ("The element in the last index of the rotor is : %zu\n" , lastIndex);
  int i ;
  int temp =rotor[27]; // holds last elements
  for (i=27; i>0; i--)  // go backwards to keep data
    {
      // printf ("the last value is %d\n ", temp); 
      //printf("The value at index: %d is %d before rotate right\n", i, rotor[i]);
      rotor[i] = rotor[i-1]; //rotate
      // printf("The value at index: %d is %d after rotate right\n", i+1 , rotor[i+1]);
    }
  rotor[0] = temp;  //switch first and last element 
  //for (i =0; i<28; i++)
  // {
      //     printf("Rotate Right : The element at index %d is %d\n", i , rotor[i]);
  // }
}


/*
This function rotates all the elements of the given rotor 
to the left 
 */
void rotateRotorLeft(int rotor[28])
{
  //printf("\nTest for rotate left*********");
  int i;
  int temp = rotor[0]; // hold first element 
  for (i =0; i<27; i++)
    {
      rotor[i] = rotor[i+1];
    }
  rotor[27] = temp;  //sw
}

// this function  takes in a rotor and 
// the amount of rotations and 
// then puts rotor1 back to its initial posistion 
void setRotor1(int rotor[28], int rotations)
{
  int i;
  for (i =0; i< rotations; i++)
    {
      rotateRotorRight(rotor);
    }
  /* for debugging
  for (i =0; i<28; i++)
    {
      printf("\n*********The element at index %d is %d\n", i , rotor[i]);
    }
  */
}

		    
/*
this function  takes in a rotor and                                                                                                
 the amount of rotations to set its initial position                                                                                                   
*/                                                                                      
void setRotor2(int rotor[28], int rotations)
{
  int i;
  for (i =0; i< rotations; i++) //for amount of given rotations
    {
      rotateRotorLeft(rotor); //rotate left
    }
  /* for debuggin
  for (i =0; i<28; i++)
    {
      printf("\n*********The element at index %d is %d\n", i , rotor[i]);
    }
  */
}
		      
/*
This method takes in a char and then converts it to it index
by first making it a capital letter and then subtracing 65 to gets its ASCII value 
 */
int charToIndex(char convert)
{
  if (convert == ' ')
    {
      return 26;
    }
  else if ( convert == '.')
    {
      return 27;
    }
  else 
    {
      convert = toupper(convert);  // convert to upper case and store in convert
      // printf("the char in upper case  is : %c\n", convert);
      int index = (int)convert-65;   //calculate index 
      //      printf("the index of the char %c is %d\n", convert, index);
      return index;
     }
}
	     
/*
 This method converts a given index into a character A-Z
 */
char indexToChar(int convert)
{
  if (convert  == 26)
    {
      return ' ';
    }
  else if ( convert == 27)
    {
      return '.';
    }
  else
    {
      char letter =(char)(convert +65);
      //printf("the char at index  %d is %c\n", convert, letter);
      return letter;
    }
}


/* 
This function takes in a file to encrypt, a file to write the encryption to 
and the rotors that will be used to encrypt the message with the enigma Machine
 */
void encryptFile(FILE* infile,FILE* outfile, int rotor1[28], int rotor2[28])
{
  int SIZE = 256;
  char inputBuffer [SIZE];
  char outString[256];
  int lineCounter =0; // counter for the lines in the string
  //  infile = fopen("rotors.ini", "r");
  //outfile = fopen("output.txt", "w");
  // This loops through the encrypting file and find the letter to encrypt  
  int rotor1Index;  // for index of rotor
  int newLine ; // to check if there is a newline 
  while(fgets(inputBuffer, SIZE, infile))  // get each line from the input file and stor it in the input buffer
    {      
      for(int i =0; i < strlen(inputBuffer); i++) // for each char in the string 
	{ 
	  char letterToEncrypt = inputBuffer[i]; // gets the current char
	  if( letterToEncrypt == '\n')   //checks for new lines 
	    {
	      newLine =1;  //if there is a  new line break out of loop 
	      break;
	    }
	  else 
	    {
	      newLine = 0; 
	    }
	  //find the index of that char in rotor1 
	  rotor1Index = charToIndex(letterToEncrypt);
	  // how search through rotor 2 to find the index and return the letter
	  char encryptedLetter = searchForIndex (rotor2, rotor1[rotor1Index]); //search rotor 2 to get encrypted char
	  //printf("The encrypted letter is %c\n", encryptedLetter);
	  outString[i] = encryptedLetter; //put the encrpyted letter into the outstring 
	  //rotate the rotors
	  rotateRotorRight(rotor1);
	  rotateRotorLeft(rotor2);
	  //put the letter into a string that will go into the output file  
	}
      if ( newLine == 1 )     // if there is a nuew line put null terminator at inputBuffer -1 and print with \n
	{
	  outString[strlen(inputBuffer)-1] = '\0';
	  fprintf(outfile, "%s\n", outString);
	}
      else if (newLine ==0) // if no new lines print with no new line
	{
	  outString[strlen(inputBuffer)] = '\0';
	  fprintf(outfile, "%s", outString);
	}
      lineCounter ++;
    }	
       fclose(infile);  //close files
      fclose(outfile);
}
  
/*
Used to decrpyt the given file
 */		
void decryptFile(FILE* infile,FILE* outfile, int rotor1[28], int rotor2[28])
{
  int SIZE = 256; //max size is 256
  char inputBuffer [SIZE]; 
  char outString[256];
  int lineCounter =0; // counter for the lines in the string                                                                   
  // This loops through the encrypting file and find the letter to encrypt                                                     
  int rotor2Index;
  int newLine;
  while(fgets(inputBuffer, SIZE, infile))  // get each line                                                                   
    {
      for(int i =0; i < strlen(inputBuffer); i++) //get each char in the string 
        {
          char letterToDecrypt = inputBuffer[i]; // gets the current char                                
	  if( letterToDecrypt == '\n')   //checks for new lines                                                                                                               
           {
              newLine =1;  //if there is a  new line break out of loop                                                                                                        
              break;
            }
          else
            {
              newLine = 0;
            }
          // find the index of that char in rotor2                                                                             
          rotor2Index = charToIndex(letterToDecrypt);
	  //  printf("The current letter is %c\n for index %d", letterToDecrypt, rotor2Index);
          // now search through rotor 2 to find the index and return the letter                                                
          char decryptedLetter = searchForIndex (rotor1, rotor2[rotor2Index]);
          //printf("The decrypted letter is %c\n", decryptedLetter);
          outString[i] = decryptedLetter;
          //printf("outString: %c\n " , outString[i]);
	  //rotate the rotors      
	  rotateRotorRight(rotor1);                                                                                           
	  rotateRotorLeft(rotor2);       
          //put the letter into a string that will go into the output file                                                     
        }
      if ( newLine == 1 )     // if there is a nuew line put null terminator at inputBuffer -1 and print with \n                                                              
        {
          outString[strlen(inputBuffer)-1] = '\0';
          fprintf(outfile, "%s\n", outString);
        }
      else if (newLine ==0) // if no new lines print with no new line                                                                                                         
        {
          outString[strlen(inputBuffer)] = '\0';
          fprintf(outfile, "%s", outString);
        }
      lineCounter++;
    }
  fclose(infile);
  fclose(outfile);  //close files 
}


/* this is a helper function - when given an index it will search 
through the a rotor and return the char at the index
*/
char searchForIndex(int rotor[28], int index)
{
  char letterAtIndex;
  for (int i =0; i<28; i++)
    {
      if (rotor[i] == index) 
	{
	  letterAtIndex = indexToChar(i);
	  //printf("We found the char %c at the index %d\n", letterAtIndex, index);
	  return letterAtIndex;
	}
      
    }
  printf("Letter not found");
  return '!'; 
}
