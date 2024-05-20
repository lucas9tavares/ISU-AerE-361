#include<stdio.h>
int main(void) {
int foo[100]; /*foo is an array of 100 integers*/
for(int i = 0 ; i < 100 ; ++i) { /*loop through all of foo: array indices 0..99 */
printf("%d\n", foo[i]);
} /*end for*/
return 0; /*terminate normally*/
} /*end main*/
