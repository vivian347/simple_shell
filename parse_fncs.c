#include "shell.h"

char **strtok_fnc(char *str, char *del);
int len_tok(char *str, char *del);
int tok_count(char *str, char *del);

/**
 * strtok_fnc - splits string into argv
 * @str: string to be split
 * @del: delimiter char
 * Return: pointer to tokenized str
 */
char **strtok_fnc(char *str, char *del)
{
    int i = 0, j, k, token, count;
    char **buff;

    token = tok_count(str, del);
    if (token == 0)
        return (NULL);
    buff = malloc(sizeof(char *) * (token + 2));
    if (!buff)
        return (NULL);
    for (j = 0; j < token; j++)
    {
        while (str[i] == *del)
            i++;
        count = len_tok(str + i, del);
        buff[j] = malloc(sizeof(char) * (count + 1));
        if (!buff[j])
        {
            for (i -= 1; i >= 0; i--)
                free(buff[i]);
            free(buff);
            return (NULL);
        }
        for (k = 0; k < count; k++)
        {
            buff[j][k] = str[i];
            i++;
        }
        buff[j][k] = '\0';
    }
    buff[j] = NULL;
    buff[j + 1] = NULL;
    return (buff);
}

/**
 * len_tok - marks end of 1st token
 * @str: string to be checked
 * @del: delim char
 * Return: del index at end of token
 */
int len_tok(char *str, char *del)
{
    int len = 0, i = 0;

    while (*(str + i) && *(str + i) != *del)
    {
        len++;
        i++;
    }
    return (len);
}

/**
 * tok_count - counts tokenized strings
 * @str: string checked
 * @del: delim char
 * Return: no of tokenized strings
 */
int tok_count(char *str, char *del)
{
    int len = 0, i, count = 0;

    for (i = 0; *(str + i); i++)
        len++;
    for (i = 0; i < len; i++)
    {
        if (*(str + i) != *del)
        {
            count++;
            i += len_tok(str + i, del);
        }
    }
    return (count);
}