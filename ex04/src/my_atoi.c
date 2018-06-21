#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int my_atoi(const char *nptr)
{
   int x, i, j;

   x = 0;
   i = strlen(nptr);
   j = 1;
   while (--i >= 0)
   {
       if ('0' <= nptr[i] && nptr[i] <= '9')
        {
            x += (nptr[i] - 48) * j;
            j *= 10;
        }
   }

   if (nptr[0] == '-')
   {
      x *= -1;
   }
   return x;
}

