/*
  Lucas Tavares
  02/08/2024

  Example code: Ask the user for a number. Ask for that number of numbers. Terminate if we get something other than a positive integer.
*/

#include<stdio.h> /* for printf */

/****************
CheckNum function
****************/

/*
int CheckNum(string UserInputString)
  -This function checks if a given char string is a positive integer.
  -Do this by looping through each character of the input string to check if it is a digit.
return 1 (for true) if the input string is a number and 0 otherwise.
  -Exit with an error message if not.
*/

/*
First get the length of the UserInputString, then
Loop and check each char is a digit
*/

StringLen = strlen(UserInputString);

Loop StringLen tumes;
isdigit(UserInputString[i]) /* check each char is a digit */

/************
main function
************/

int main(void) {

  int MAX_STRING_LEN=100;
  char UserInputString[MAX_STRING_LEN];
  int NumOfNums;

/* First ask the user for a number of numbers; print this to stdout. */
  printf("Please enter a number: \n");
  
/* Read in the number that the user typed on the command line. Save it to UserInputString. */
  scanf("%s", UserInputString);
  printf("I got: %s\n", UserInputString); /* test that the scanf worked */
  
/*
Check that the number that the user gave is a positive integer.
  -If the user's number is not an integer, or not positive, print an error message and exit.
  -Otherwise, proceed to my loop.

  CheckNum(NumOfNums);

  -Here, we know the number of numbers is a number, so save it to NumOfNums.
*/

/* Loop NumOfNums times. Each time, ask for a number and check that it is really a number. Exit if not. */
  for (int i = 0; i < NumOfNums; i++) {
    /* ask for a number */
    /* check that it is really a number. Exit if not. Do this by calling my function. */
  } /* end for */
  
/* If we get here, we were successful! Done! */
  return 0;
} /* end main */
