#include "shell.h"

int _strcmp(const char *str1, const char *str2);

/**
 * _strcmp - compares 2 strings
 * @str1: first string
 * @str2: 2nd string
 *
 * Return: 0 if equal
 */

int _strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}