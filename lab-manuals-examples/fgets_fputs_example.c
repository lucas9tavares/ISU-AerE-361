/* using fgets() and fputs() */

#include <stdio.h>

#define MAXLINE 20 /*MAXLINE is our constant, hard-coded in by the C pre-processor*/

int main(void) {
  char line[MAXLINE]; /*a line is an array of characters MAXLINE long*/
  while (fgets(line, MAXLINE, stdin) != NULL &&
	  line[0] != '\n') {
    fputs(line, stdout);
  } /*end while*/
  
  return 0; /*terminate normally*/
} /*end main*/
