#include <stdio.h> /*both scanf and printf are included in this file*/
#include <string.h> /*string also needs to be included*/

int main (int argc, char **argv){

  char s[100]; /*declare a 100-character array*/

  while (1){ /*NOTE: Be VERY careful when writing infinite loops!!!*/

    printf ("Please input something (length not exceeding 100):\n");
    scanf ("%s", s); /*read in character ’s’ */
    printf ("Your input is: %s\n", s); /*print out s for debugging*/

    if (strcmp (s, "0") == 0){ /*an important test*/
      break; /*break out of the ’while’ loop*/
    } /*end if*/

  } /*end while*/

  return 0; /*terminate normally*/

} /*end main*/
