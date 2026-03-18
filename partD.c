#include <stdio.h>
#include <ctype.h>

int charToIndex(char convert);

int main (void)
{
  char letter = 'h';
  charToIndex(letter);
  return 0; 
}

int charToIndex(char convert)
{

  convert = toupper(convert);
  printf("the char in upper case  is : %c\n", convert);
  int index = (int)convert-65;
  printf("the index of the char %c is %d\n", convert, index);
  return index;
}
