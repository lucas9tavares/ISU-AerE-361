/*

  Lucas Tavares
  02/19/2024

  Prompt the user for an integer n, output a file named ans.out with a n x n matrix such that all the integer numbers between 1 and n^2 are stored in the matri following a spiral pattern.

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


/****************
CheckNum function
****************/

/* First get the length of the userInput, then loop and check each char is a digit, and check it is within the stablished range */

int CheckNum(char userInput[]) {

  int StringLen = strlen( userInput );
  int ans = 0;

  for (int i = 0; i < StringLen; ++i) {
    if (!isdigit(userInput[i])) {
      ans = 1;
      break;
    }
  } /*end for*/

  if ( ans == 0 ) {
    int userInputInt = atoi(userInput);

    if ( userInputInt >= 1 && userInputInt <= 100 ) { /* Check the value is within the range */
      ans = 0;
    } /*end if*/
    else { 
      ans = 1;
    } /*end else*/
  } /*end outermost if*/
 
  return ans;
  
} /*end CheckNum */


/*******************
countDigits function
*******************/

/* Count how many digits an integer have */

int countDigits(int num) {

  int count = 0;

  while ( num != 0 ) {
      num /= 10;
      count++;
  } /*end while*/

  return count;
  
} /*end countDigits*/


/************
main function
************/

int main(void) {

  char userInput[256];

  /* First ask the user for an integer */
  printf("Please enter an integer from 1 to 100: \n");
  scanf("%s", userInput);

  int myReturn = 0;
  
  if (CheckNum( userInput ) == 0) { /* Check that the number that the user gave is an integer,  >= 1 and <= 100 */

    int n = atoi(userInput);

    /* Dynamically allocate the matrix n by n in size */
    int ** matrix;
    matrix = malloc(sizeof(int *) * n);
    for ( int j = 0; j < n; ++j ) {
      matrix[j] = malloc(sizeof(int) * n);
    } /*end for*/

    /* Fill the matrix */
    int x;
    int y;
    if ( n % 2 == 0 ) {
      x = ceil(n/2 - 1);
      y = ceil(n/2 - 1);
    } /*end if*/
    else {
      x = ceil(n/2);
      y = ceil(n/2);
    } /*end else*/
    int d = 0;
    int c = 1;
    int s = 0;

    for ( int k = 1; k < n; k++ ) {
      for ( int l = 0; l<(k<(n-1)?2:3); l++ ) {
	for ( int m = 0; m <= s; m++ ) {
	  matrix[x][y] = c; /* Save "c" to the matrix position x, y */
	  c++;
	  switch (d) {
	    case 0:
	      y = y + 1;
	      break;
	    case 1:
	      x = x + 1;
	      break;
	    case 2:
	      y = y - 1;
	      break;
	    case 3:
	      x = x - 1;
	      break;
          } /*end switch*/
	} /*end for (m from 0 to s) */
        d = (d+1)%4;
      } /*end for*/
      s = s + 1;
    } /*end outermost for loop*/

    matrix[x][y] = c; /* Do the last iteration */
    
    /* Set number width */
    int nSquared = pow(n,2);
    int width = countDigits(nSquared);

    /* Print the matrix into ans.out */

    FILE * file;
    file = fopen("ans.out", "w");

    for ( int o = 0; o < n; o++ ) {

      for (int p = 0; p < n; p++ ) {
	fprintf(file, "%*d ", width, matrix[o][p]);
      } /*end inner for*/

      fprintf(file, "\n");

    } /*end outer for*/

    fclose(file);

    myReturn = 0;
    
  } /*end if*/
  
  else {
    printf("That is not a valid input. \n");
    myReturn = 1;
  } /*end else*/
  
  return myReturn;
  
} /* end main */
