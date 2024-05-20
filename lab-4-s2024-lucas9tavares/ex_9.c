/*
  Lucas Tavares
  02/12/2024

  Prompt the user for a number of loop times, rach time it loops ask prompt the user for a char.
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

/****************
CheckChar function
****************/

/* Check if the user input is a single letter */

int CheckChar(char UserInputChar[]) {

  int StringLen = strlen( UserInputChar );
  int ans;

  if ( StringLen > 1 ) { /* Check if the string has more than 1 char */
    ans = 1;  
  }
  else if ( isalpha(UserInputChar[0]) ) { /* Check if the char is a letter */
    ans = 0;
  }
  else { 
    ans = 1;
  }
    
  return ans;
  
} /*end CheckChar */
    
/************
main function
************/

int main(void) {

  int MAX_STRING_LEN = 256;
  char UserInputString[MAX_STRING_LEN];
  char UserInputChar[MAX_STRING_LEN];
  int myReturn = 0;
  
  /* First ask the user for a number of loops, read the number that the user typed in the command line, and save it to UserInputNumber */
  printf("Hello! How many chars should I take? ");
  scanf("%s", UserInputString);

  if (CheckNum( UserInputString ) == 0) {

    int UserInputNumber;
    sscanf(UserInputString, "%d", &UserInputNumber);
  
    /* Ask the user for the first char, loop the number of times the user answered for the other chars, checking if every char is valid */
    printf("Please give me a char: ");
    scanf("%s", UserInputChar);

    if ( CheckChar(UserInputChar) == 0) {

      for ( int i = 1; i < UserInputNumber; ++i ) {

        printf("Thanks! Please give me another char: ");
        scanf("%s", UserInputChar);

        if ( CheckChar(UserInputChar) == 1) {
	  printf("Invalid input. \n");
	  myReturn = 1;
	  break;
        }

      }

    }
    else {
      printf("Invalid input. \n");
      myReturn = 1;
    }

    if ( myReturn == 0) {
      printf("Thanks! I am happy with %d chars. \n", UserInputNumber);
    }

  }

  else {
    printf("That is not an integer. \n");
    myReturn = 1;
  }  
  
  return myReturn;
  
} /* end main */
