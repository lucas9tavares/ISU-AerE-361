/*

  Lucas Tavares
  02/06/2024

  Write a description of the program here!
  This program prints "Hello World!" then exits.

*/

#include<stdio.h>
#include<stdlib.h>

int myfunction(void) {

  int a = 2;
  
  printf("Hi! I'm a function!\n");

  if (a == 2) {
    fprintf(stderr, "a was 2\n");
    return a;
  } /*end if */

  /*if we ger here, a was not 2*/
  printf("a was NOT 2\n"); /* equivalent to fprintf(stout, ".."); */
  
  return a;
  
} /*end myfunction*/


/* Start the program, print "Hello World!" then exit */

int main (void) {

  int my_return = 0;
  
  printf("Hello World!\n");

  my_return = myfunction();
  printf("Back in main! My return value was %d\n", my_return);
  
  return 0;
} /*end main*/


/*

  To run the code:
  
  gcc HiWorld.c    (compile the script)
  ./a.out          (run the script)

*/
