/*

  Lucas Tavares
  03/18/2024

  Header for numerical integrations.

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#ifndef INTEGRATION_H
#define INTEGRATION_H

//integral structure
struct integral {
  double (*integrand)(double);
  double low;
  double high;
};

// Midpoint Rule
double midpoint(struct integral *integral);

// Simpson's 1/3
double simpson_13(struct integral *integral);

// Simpson's 3/8
double simpson_38(struct integral *integral);

// Gauss Quad
double gauss_quad(struct integral *integral, int n);

#endif //INTEGRATION_H
