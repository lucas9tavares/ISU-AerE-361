/*

  AerE 361, Lab 5
  Lucas Tavares

  Prompt the user for a filename, try to open the file, return an error message if it already exists, create a new file if it does not exists, print the numbers 1 to 100 to the new file, 1 number per line.

*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

int main (void) {

  char filename[MAXLINE];
  printf("Please insert the file name: ");
  scanf("%s", filename); /*collect file name from the user */

  FILE * file;
  int myReturn = 0;
  int i;

  file = fopen(filename, "r");

  if (file != NULL) { /*check if file exists */
    myReturn = 1;
    fprintf(stderr, "ERROR - File already exists; Ending with return %d\n", myReturn); /*indicate an error and end execution */
  } /*end if*/

  else {

    /* close and reopen file in writing mode" */
    free(file);
    file = fopen(filename, "w");

    for (i = 1; i < 100; i++) {
      fprintf(file, "%d\n", i); /*print number to line in the file */
    } /*end for*/

    fprintf(file, "100"); /*print 100 without creating a new line */

  } /*end else*/

  fclose(file);

  return myReturn;
  
 } /*end main*/
