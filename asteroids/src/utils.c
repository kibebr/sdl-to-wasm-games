#include <stdlib.h>
#include <math.h>
#include "utils.h"

#define PI 3.141592653589793238462643383279502884

int randFromRange(int min, int max)
{
  return (rand() % (max + 1 - min) + 0);
}

double deg2rad(double degrees)
{
  return (degrees * PI) / 180;
}
