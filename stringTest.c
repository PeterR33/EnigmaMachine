#include<stdio.h>
#include<string.h>

void remopveExtraNewLine(char*);
int main (void)
{
  char a[] =" asdljfasd;fj asdlfkj \n a;lsdkjfalsdf;alksjdflda\n";
    int count =0; 
   for(int i =0; a[i] != '\0'; i++)
      {
       remopveExtraNewLine(a);
    printf("Modified string: %s\n", a);
	if (a[i] == '\n')
	  {
	    count++;
	  }
	outString[strlen(inputBuffer)] = '\0';
      } 
    printf("the amount of \\n is %d", count);
	return 0; 
}
void remopveExtraNewLine(char *ptr)
{
  while((*ptr != '\0')&& (*ptr != '\n'))
    {
      ptr++;
    }
  *ptr = '\0';
}

if (inputBuffer[strlen-1] == '\n'
  {
    fprintf (
