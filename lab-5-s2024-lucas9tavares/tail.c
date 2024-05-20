/*

  AerE 361, Lab 5
  Lucas Tavares

  Prompt the user for a filename, try to open the file, return an error message if it doesn't exists, read the last 3 lines if the file opens.

*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

int main (void) {

  char filename[256];
  printf("Please insert the file name: ");
  scanf("%s", filename); /*collect filne name from the user */

  FILE * file;
  int myReturn = 0;
  int i;
  char line[3][MAXLINE];
  int numLines = 0;

  file = fopen(filename, "r");

  if (file == NULL) { /*check if file exists */
    myReturn = 1;
    fprintf(stderr, "ERROR - File not found; Ending with return %d\n", myReturn); /*indicate an error and end execution */
    free(file);
  } /*end if*/

  else {
    while (fgets(line[numLines % 3], MAXLINE, file) != NULL) { /*read last 3 lines */
        numLines++;
    } /*end while*/
    
    for (i = 0; i < 3; i++) {
      printf("%s\n", line[i]); /*print line content */
    } /*end for*/

    fclose(file);
    
  } /*end else*/

  return myReturn;
  
 } /*end main*/
