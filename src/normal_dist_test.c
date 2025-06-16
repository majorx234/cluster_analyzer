// normal_distribution
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

double sampleNormal(double mean) {
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return sampleNormal(mean);
    double c = sqrt(-2 * log(r) / r);
    return u * c + mean;
}

double sampleNormal2(double mean, double sigma) {
    const double two_pi = 2.0 * M_PI;
    double u1, u2;
    do
    {
        u1 = ((double) rand() / (RAND_MAX));
    }
    while (u1 == 0);
    u2 = ((double) rand() / (RAND_MAX));

    //compute z0 and z1
    double mag = sigma * sqrt(-2.0 * log(u1));
    double z0  = mag * cos(two_pi * u2) + mean;
    double z1  = mag * sin(two_pi * u2) + mean;

    return z0; // z1 is rand too
}

int main()
{
  const int nrolls=10000;  // number of experiments
  const int nstars=100;    // maximum number of stars to distribute

  int p[10]={0};

  for (int i=0; i<nrolls; ++i) {
    double number = sampleNormal(5.0);
    if ((number>=0.0)&&(number<10.0)) ++p[(int)number];
  }

  for (int i=0; i<10; ++i) {
    printf("%d-%d:",i,i+1);
    double num_stars = p[i]*nstars/nrolls;
    for( int j=0;j<num_stars;j++){
      printf("*");
    }
    printf("\n");
  }

  // 2nd aproach
  for (int i=0; i<nrolls; ++i) {
    double number = sampleNormal2(5.0, 1.0);
    if ((number>=0.0)&&(number<10.0)) ++p[(int)number];
  }

  for (int i=0; i<10; ++i) {
    printf("%d-%d:",i,i+1);
    double num_stars = p[i]*nstars/nrolls;
    for( int j=0;j<num_stars;j++){
      printf("*");
    }
    printf("\n");
  }


  return 0;
}
