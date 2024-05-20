/*
  Lucas Tavares
  02/12/2024

  Prompt the user for a number, output if the user input is or is not an integer.
*/

#include<stdio.h>
#include <string.h>
#include <ctype.h>

/****************
CheckNum function
****************/

/*
First get the length of the UserInputString, then
Loop and check each char is a digit
*/

int CheckNum(char UserInputString[]) {

  int StringLen = strlen( UserInputString );
  int ans = 0;
  int i = 0;

  if ( UserInputString[0] == '-' || isdigit(UserInputString[0]) ) { /* Check if the first char is a - sign */
  
    for ( int i = 1; i < StringLen; ++i ) { /* Check each char is a digit */
   
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
    
/************
main function
************/

int main(void) {

  int MAX_STRING_LEN = 100;
  char UserInputString[MAX_STRING_LEN];

/* First ask the user for a number of numbers; print this to stdout. */
  printf("Please enter a number: \n");
  
/* Read in the number that the user typed on the command line. Save it to UserInputString. */
  scanf("%s", UserInputString);
  
/* Check that the number that the user gave is an integer. */
  int myReturn = 0;
  
  if (CheckNum( UserInputString ) == 0) {
    printf("That is an integer \n");
    myReturn = 0;
  }
  else {
    printf("That is not an integer \n");
    myReturn = 1;
  }

  return myReturn;
  
} /* end main */
