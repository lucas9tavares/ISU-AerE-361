
#include <stdio.h>
#include <math.h>

double integrand(double x){
    // Your test function goes here
    return x*x;
}

// Forword declaration of function prototypes here

double midpoint(double (*integrand)(double), double a, double b);

double simpson_13(double (*integrand)(double), double a, double b);

double simpson_38(double (*integrand)(double), double a, double b);

double gauss_quad(double (*integrand)(double), double a, double b, int n);


int main(void) {

  double ans;
  double a = 4;
  double b = 8;

  ans = midpoint(integrand, a, b);
  printf("Midpoint integration: %g\n", ans);

  ans = simpson_13(integrand, a, b);
  printf("Simpson's 1/3 Rule: %g\n", ans);

  ans = simpson_38(integrand, a, b);
  printf("Simpson's 3/8 Rule: %g\n", ans);

  int n = 3;
    
  ans = gauss_quad(integrand, a, b, n);
  printf("Gauss Quad: %g\n", ans);

  return 0;

}
