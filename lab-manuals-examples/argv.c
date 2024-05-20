#include <stdio.h>

int main (int argc, char **argv){

  int i = 0; /*loop variable*/

  for (i = 0; i < argc; i ++){ /*loop through all command-line arguments*/

    /*print each argument to the screen*/
    printf ("Argument %d: %s\n", i, argv[i]);

  } /*end for*/

  return 0; /*terminate without error*/

} /*end main*/
