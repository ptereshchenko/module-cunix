#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_puts(const char *s)
{
  int i;
  char x;

  i = -1;
  while (++i < strlen(s))
  {
    x = s[i];
    write(1, &x, 1);
  }
    x = '\n';
    write (1, &x, 1);
  return 0;
}
