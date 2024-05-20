/*

  Lucas Tavares
  02/19/2024

  Prompt the user for the size of an array, set the value of each element of the array according to the formula provided, ask the user for an element to retrive from the array, print the value retrieved

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

/****************
CheckNum function
****************/

/*
First get the length of the UserInputString, then
Loop and check each char is a digit
*/

int CheckNum(char userInput[]) {

  int StringLen = strlen( userInput );
  int ans = 0;
  int i = 0;

  for ( int i = 0; i < StringLen; ++i ) { /* Check each char is a digit */
   
    if ( isdigit(userInput[i]) ) {
      ans = 0;
    }
    else {
      ans = 1;
      break;
    }
  
  }

  if ( ans == 0 ) {
    int userInputInt = atoi(userInput);

    if ( userInputInt >=1 && userInputInt <= 250 ) {
      ans = 0;
    }
    else { 
      ans = 1;
    }
  }
    
  return ans;
  
} /*end CheckNum */
    
/************
main function
************/

int main(void) {

  char userInput[256];

  /* First ask the user for the size of the array */
  printf("Please enter the size of the array (max 250): \n");
  scanf("%s", userInput);

  int myReturn = 0;
  
  if (CheckNum( userInput ) == 0) { /*check that the number that the user gave is an integer  >= 1 and <= 250 */

    int userInputInt = atoi(userInput);
    float * array;
    array = malloc(sizeof(float) * userInputInt);

    for ( int j = 0; j < userInputInt; ++j ) {
      array[j] = 1 + pow(j,2) + ( pow(j,3) / 3);
    }

    char userInput2[256];
    printf("Please enter an element to be retrieved: \n");
    scanf("%s", userInput2);
    int userInput2Int = atoi(userInput2);

    if (CheckNum( userInput2 ) == 0 && userInput2Int <= userInputInt) { /*check that the input is a valid element of the array */

      float element = array[userInput2Int-1];
      printf("%f\n", element);

      myReturn = 0;

    }

    else {
      printf("That is not a valid input. \n");
      myReturn = 1;
    }
    
  }
  else {
    printf("That is not a valid input. \n");
    myReturn = 1;
  }

  return myReturn;
  
} /* end main */
