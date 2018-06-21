#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* my_itoa(int nmb)
{
  int i, j, k, n;

  i = 10;
  j = 0;
  k = 0;
  n = 0;
  while (nmb / i != 0)
  {
    i *= 10;
    j++;
  }
  char *x = malloc (sizeof (char) * j + 1);
  i = 0;

  if (nmb < 0)
  {
    n = 1;
    nmb *= -1;
    x[0] = '-';
    k++;
    j++;
  }
  while (j >= k)
  {
    x[j] = (nmb % 10) + '0';
    nmb /= 10;
    j--;
  }
  return x;
}
