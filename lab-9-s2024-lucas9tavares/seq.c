/*

  Lucas Tavares
  04/01/2024

  Generate the first n terms in the sequece given by the difference equation provided.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/************
main function
************/

int main(int argc, char *argv[]) {

  //Check if command line argunts are inserted correctly 
  if (argc > 2) {
    fprintf(stderr, "Invalid arguments structure \n");
    fprintf(stderr, "Usage: %s -<flag> \n", argv[0]);
    return 1;
    exit(1);
  } //end if
  
  //Double precision calculation
  if (argc == 2) {

    //Check if flag is a valid input
    const char * flag = &argv[1][1];
    if (strcmp(flag, "d") != 0 || strlen(argv[1]) > 2) {
      fprintf(stderr, "Invalid flag argument: Flag must be '-d' for double precision or no flag for single precision \n");
      fprintf(stderr, "Usage: %s -<flag> \n", argv[0]);
      return 1;
      exit(1);
    } //end if

    //Calculate and print first and second terms
    int n = 20;
    double x[n];
    x[0] = 11.0 / 2.0;
    x[1] = 61.0 / 11.0;

    printf("x1 = %f \n", x[0]);
    printf("x2 = %f \n", x[1]);

    //Calculate and print terms 3 to 20
    int k;
    for (k = 1; k < (n - 1); k++) {
      x[k+1] = 111.0 - (1130.0 - 3000.0 / x[k-1]) / x[k];
      printf("x%d = %f \n", (k + 2), x[k+1]);
    } //end for

    return 0;
    exit(0);
    
  } //end if

  //Single precision calculation
  
  //Calculate and print first and second terms
  int n = 10;
  float x[n];
  x[0] = 11.0 / 2.0;
  x[1] = 61.0 / 11.0;

  printf("x1 = %f \n", x[0]);
  printf("x2 = %f \n", x[1]);

  //Calculate and print terms 3 to 10
  int k;
  for (k = 1; k < (n - 1); k++) {
    x[k+1] = 111.0 - (1130.0 - 3000.0 / x[k-1]) / x[k];
    printf("x%d = %f \n", (k + 2), x[k+1]);
  } //end for

  return 0;

} //end main
