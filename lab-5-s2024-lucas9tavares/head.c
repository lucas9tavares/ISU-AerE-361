/*

  AerE 361, Lab 5
  Lucas Tavares

  Prompt the user for a filename, try to open the file, return an error message if it doesn't exists, rad the first 3 lines if the file opens.

*/

#include <stdio.h>
#include <stdlib.h>


int main (void) {

  char filename[100];
  printf("Please insert the file name: ");
  scanf("%s", filename); /*collect filne name from the user */

  FILE * file;
  int myReturn = 0;
  int i;
  char * line;
  size_t lineLen;
  file = fopen(filename, "r");

  if (file == NULL) { /*check if file exists */
    myReturn = 1;
    fprintf(stderr, "ERROR - File not found; Ending with return %d\n", myReturn); /*indicate an error and end execution */
    free(file);
  } /*end if*/

  else {
    for (i = 0; i < 3; i++) {
      getline(&line, &lineLen, file); /*get line content */
      printf("%s", line); /*print line content */
    } /*end for*/

    fclose(file);
    
  } /*end else*/

  return myReturn;
  
 } /*end main*/
