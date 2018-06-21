#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

 unsigned int my_strlen(char *str)
  {
      int i;
 
      i = 0;
      while (str[i] != '\0')
       i++;
      return i;
  }
 
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
int my_atoi(char *nptr)
  {
    int x, i, j;
 
    x = 0;
    i = my_strlen(nptr);
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
void my_printf(const char *format, ...)
  {
    int total, count , arg1, size, i, loop_count, w, z;
    char token, *arg3, *tmp, temp;
    va_list ap;
    
    char zr = '0';
    char wse = ' ';
    count = 0;
    w = 0;
    z = 0;
    va_start(ap, format);

    while (*format != '\0')
      {
       if (*format == '%')
         {
        if (*(format + 1) == '0')
          {
            z = 1;
            format++;
          }
       else z = 0;

     if (*(format + 1) >= '1' && *(format + 1) <= '9')
        {
         while ((temp = *(++format)) >= '0' && temp <= '9')
            count++;
            tmp = (char*)malloc(count * sizeof(char));
            format -= count;
         for (i = 0; i < count; i++)
            *(tmp + i) = *(format++);
            w = my_atoi(tmp);
            format--;
            count = 0;
        }
      token = *(++format);
  
    switch (token)
     {
      case 'd':
        arg3 = my_itoa(va_arg(ap, int));
        size = my_strlen(arg3);
        loop_count = w - size;
     if (!z)
     for (i = 0; i < loop_count; i++)
        write(1, &wse, sizeof(char));
     else
        if (z)
        for (i = 0; i < loop_count; i++)
          write(1, &zr, sizeof(char));
        for (i = 0; i < size; i++)
          write(1, &arg3[i], sizeof(char));
        break;
     case '%':
        write(1, &token, sizeof(token));
        break;
     case 's':
        arg3 = va_arg(ap, char *);
        size = my_strlen(arg3);
        loop_count = w - size;
       if (!z)
       for (i = 0; i < loop_count; i++)
          write(1, &wse, sizeof(char));
       else
       if (z)
       for (i = 0; i < loop_count; i++)
          write(1, &zr, sizeof(char));
       for (i = 0; i < size; i++)
          write(1, &arg3[i], sizeof(char));
       break;
   }
  }
  else write(1, &(*format), sizeof(*format));
    format++;
 }
}

