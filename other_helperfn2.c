#include "shell.h"

ssize_t new_len(char *arg);
void log_oper(char *ptr, ssize_t *ptr_new);
void split_line(char **ptr, ssize_t len);

/**
 * split_line - splits line read
 * @ptr: pointer to line read
 * @len: length of line
 * Return: void
 */
void split_line(char **ptr, ssize_t len)
{
    size_t i, j;
    ssize_t len_new;
    char *line, *line_new, curr;
    char prev, fol;

    len_new = new_len(*ptr);
    if (len_new == read - 1)
        return;
    line_new = malloc(len_new + 1);
    if (!line_new)
        return;
    j = 0;
    line = *ptr;
    for (i = 0; line[i]; i++)
    {
        curr = line[i];
        fol = line[i + 1];
        if (i != 0)
        {
            prev = line[i - 1];
            if (curr == ';')
            {
                if (fol = ';' && prev != ' '
                    && prev != ';')
                {
                    line_new[j++] = ' ';
                    line_new[j++] = ';';
                    continue;
                }
                else if (prev == ';' && fol != ' ')
                {
                    line_new[j++] = ';';
                    line_new[j++] = ' ';
                    continue;
                }
                if (prev != ' ')
                    line_new[j++] = ' ';
                line_new[j++] = ';';
                if (fol != ' ')
                    line_new[j++] = ' ';
                continue;
            }
            else if (curr == '&')
            {
                if (fol == '&' && prev != ' ')
                    line_new[j++] = ' ';
                else if (prev == '&' && fol != ' ')
                {
                    line_new[j++] = '&';
                    line_new[j++] = ' ';
                    continue;
                }
            }
            else if (curr == '|')
            {
                if (fol == '|' && prev != ' ')
                    line_new[j++] = ' ';
                else if (prev == '|' && fol != ' ')
                {
                    line_new[j++] = '|';
                    line_new[j++] = ' ';
                    continue;
                }
            }
        }
        else if (curr == ';')
        {
            if (i != 0 && line[i - 1] != ' ')
                line_new[j++] = ' ';
            line_new[j++] = ';';
            if (fol != ' ' && fol != ';')
                line_new[j++] = ' ';
            continue;
        }
        line_new[j++] = line;
    }
    line_new[j] = '\0';
    free(*ptr);
    *ptr = line_new
}

/**
 * new_len - get len of split line
 * @arg: line to get length
 * Return: length
 */
ssize_t new_len(char *arg)
{
    ssize_t len = 0;
    size_t i;
    char curr, fol;

    for (i = 0; arg[i]; i++)
    {
        curr = arg[i];
        fol = arg[i + 1];
        if (curr == '#')
        {
            if (i == 0 || arg[i - 1] == ' ')
            {
                arg[i] = '\0';
                break;
            }
        }
        else if (i != 0)
        {
            if (curr == ';')
            {
                if (fol == ';' && arg[i - 1] != ' '
                    && arg[i - 1] != ';')
                {
                    len += 2;
                    continue;
                }
                else if (arg[i - 1] == ';' && fol != ' ')
                {
                    len += 2;
                    continue;
                }
                if (arg[i - 1] != ' ')
                    len++;
                if (fol != ' ')
                    len++;
            }
            else
                log_oper(&arg[i], &len);
        }
        else if (curr == ';')
        {
            if (i != 0 && arg[i - 1] != ' ')
                len++;
            if (fol != ' ' && fol != ';')
                len++;
        }
        len++;
    }
    return (len);
}

/**
 * log_oper - checks for || and &&
 * @ptr: points to oper to check
 * @ptr_new: points to len
 * Return: void
 */
void log_oper(char *ptr, ssize_t *ptr_new)
{
    char fol, curr, prev;

    fol = *(ptr + 1);
    prev = *(ptr - 1);
    curr = *ptr;
    if (curr == '&')
    {
        if (fol == '&' && prev != ' ')
            (*ptr_new)++;
        else if (prev == '&' && fol != ' ')
            (*ptr_new)++;
    }
    else if (curr == '|')
    {
        if (fol == '|' && prev != ' ')
            (*ptr_new)++;
        else if (prev == '|' && fol != ' ')
            (*ptr_new)++;
    }
}