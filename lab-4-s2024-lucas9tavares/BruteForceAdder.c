/*
  Lucas Tavares
  02/12/2024

  Prompt the user for an integer, check if it is an integer, print the number, add the numbers from 1 to the input number using a loop.

*/


#include<stdio.h>
#include <string.h>
#include <ctype.h>


/****************
CheckNum function
****************/

/* First get the length of the UserInputString, then loop and check each char is a digit */

int CheckNum(char UserInputString[]) {

  int StringLen = strlen( UserInputString );
  int ans = 0;
  int i = 0;

  if ( UserInputString[0] == '-' || isdigit(UserInputString[0]) ) { /* Check if the first char is a - sign or a digit */
  
    for ( int i = 1; i < StringLen; ++i ) { /* Check if each char is a digit */
   
      if ( isdigit(UserInputString[i]) ) {
        ans = 0;
      }
      else {
        ans = 1;
        break;
      }
  
    }
    
  }
  else { 
    ans = 1;
  }
    
  return ans;
  
} /*end CheckNum */


/***********************
BruteForceAdder function
***********************/

/* Using a for loop, add all number from 1 to n */

int BruteForceAdder(int n) {

  printf("BruteForceAdder started to add the numbers from 1 to %d \n", n);

  int sum = 0;
  
  for ( int j = 0; j < n; ++j ) {
    sum = sum + (j + 1);
  }

  printf("The sum of all integers from 1 to %d is equal to: %d \n", n, sum);

} /* end BruteForceAdder */

	 
/************
main function
************/

int main(void) {

  int MAX_STRING_LEN = 100;
  char UserInputString[MAX_STRING_LEN];

/* First ask the user for an integer; print this to stdout. */
  printf("Please enter an integer: \n");
  
/* Read in the number that the user typed on the command line. Save it to UserInputString. */
  scanf("%s", UserInputString);
  
/* Check that the number that the user gave is an integer. */
  int myReturn = 0;
  
  if (CheckNum( UserInputString ) == 0) {

    int n;

    sscanf(UserInputString, "%d", &n);
    printf("The chosen number was: %d \n", n);

    BruteForceAdder(n);
    
  }
  
  else {

    printf("That is not an integer. \n");
    myReturn = 1;

  }

  return myReturn;
  
} /* end main */
