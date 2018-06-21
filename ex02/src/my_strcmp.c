#include <stdio.h>
#include <string.h>

int my_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;

    while (str1[i] != '\0')
    {
        if (str1[i] < str2[i])
        {
           return -1;
        } else if (str1[i] > str2[i])
        {
           return 1;
        }
       i++;
    }
       if (str2[i] != '\0')
       {
         return -1;
       }
       else
       {
         return 0;
       }

}
