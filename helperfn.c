#include "shell.h"

int cmp(char *str1, char *str2)
{
    int flag = 0;

    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            flag = 1;
        }
        str1++;
        str2++;
    }
    if (flag == 0)
    {
        return (0);
    }
    else
    return (1);
}
char *concat(char *s1, char *s2) {
	int i, j;
	i = strlen(s1);
	for (j = 0; s2[j] != '\0'; i++, j++) {
		s1[i] = s2[j];
	}
	s1[i] = '\0';
    return (s1);
}