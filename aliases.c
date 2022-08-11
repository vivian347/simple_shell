#include "shell.h"

int alias_shell(char **args, char __attribute__((__unused__)) **start);
void alias_prt(alias_t *alias);
char **alias_rep(char **args);
void al_set(char *name, char *val);

/**
 * alias_shell - prints and sets alias
 * @args: array of arg
 * @start: points to begin of args
 * Return: -1 on error 0 on success
 */
int alias_shell(char **args, char __attribute__((__unused__)) **start)
{
    int rtn = 0, i;
    char *val;
    alias_t *ptr = aliases;

    if (!args[0])
    {
        while (ptr)
        {
            alias_prt(ptr);
            ptr = ptr->next;
        }
        return (rtn);
    }
    for (i = 0; args[i]; i++)
    {
        ptr = aliases;
        val = strchr_fnc(args[i], '=');
        if (!val)
        {
            while (ptr)
            {
                if (cmp(args[i], ptr->name) == 0)
                {
                    alias_prt(ptr);
                    break;
                }
                ptr = ptr->next;
            }
            if (!ptr)
                rtn = create_err(args + i, 1);
        }
        else
            al_set(args[i], val);
    }
    return(rtn);
}

/**
 * al_set - sets an alias
 * @name: name of alias 
 * @val: value of alias
 * Return: void
 */
void al_set(char *name, char *val)
{
    int i, j, len;
    char *val_new;
    alias_t *ptr = aliases;

    *val = '\0';
    val++;
    len = get_len(val) - initlen_sub(val, "'\"");
    val_new = malloc(sizeof(char) * (len + 1));
    if (!val_new)
        return;
    for (i = 0, j = 0; val[i]; i++)
    {
        if (val[i] != '\'' && val[i] != '"')
            val_new[j++] = val[i];
    }
    val_new = '\0';
    while (ptr)
    {
        if (cmp(name, ptr->name) == 0)
        {
            free(ptr->value);
            ptr->value = val_new;
            break;
        }
        ptr = ptr->next;
    }
    if (!ptr)
        endalias_add(&aliases, name, val_new);
}

/**
 * alias_prt - prints alias
 * @alias: 
 * Return: void
 */
void alias_prt(alias_t *alias)
{
    int len = get_len(alias->name) + get_len(alias->value) + 4;
    char *ptr;
    
    ptr = malloc(sizeof(char) * (len+ 1));
    if (!ptr)
        return;
    cpy_str(ptr, alias->name);
    cat_str(ptr, "='");
    cat_str(ptr, alias->value);
    cat_str(ptr, "'\n");
    write(STDOUT_FILENO, ptr, len);
    free(ptr);
}

char **alias_rep(char **args)
{
    int i;
    char *val_new;
    alias_t *ptr;

    if (cmp(args[0], "alias") == 0)
        return (args);
    for (i = 0; args[i]; i++)
    {
        ptr = aliases;
        while (ptr)
        {
            if (cmp(args[i], ptr->name) == 0)
            {
                val_new = malloc(sizeof(char) * (get_len(ptr->value) + 1));
                if (!val_new)
                {
                    free_args(args, args);
                    return (NULL);
                }
                cpy_str(val_new, ptr->value);
                free(args[i]);
                args[i] = val_new;
                i--;
                break;
            }
            ptr = ptr->next;
        }
    }
    return (args);
}
