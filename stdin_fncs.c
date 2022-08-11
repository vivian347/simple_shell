#include "shell.h"

char *fetch_cmd(char *buff, int *ret);
int cmd_handler(int *ret);
int exec_cmd(char **args, char **start, int *ret);
int check_cmd(char **args);
int arg_call(char **args, char **start, int *ret);

/**
 * fetch_cmd - gets cmd
 * @buff: stores cmd
 * @ret: return value
 * Return: pointer to cmd on success
 * NULL on failure
 */
char *fetch_cmd(char *buff, int *ret)
{
    char *out = "$ ";
    size_t i = 0;
    ssize_t read;

    if (buff)
        free(buff);
    read = _getline(&buff, &i, STDIN_FILENO);
    if (read == -1)
        return (NULL);
    if (read == 1)
    {
        hist++;
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, out, 2);
        return (fetch_cmd(buff, ret));
    }
    buff[read - 1] = '\0';
    rep_var(&buff, ret);
    split_line(&buff, read);
    return (buff);
}

/**
 * cmd_handler - does operations on cmd
 * @ret: return value
 * Return: value of last exec cmd
 * -1 on fail to split
 * -2 on eof
 */
int cmd_handler(int *ret)
{
    int i, res = 0;
    char **args, *buff = NULL;
    char **start;

    buff = fetch_cmd(buff, ret);
    if (!buff)
        return (END_OF_FILE);
    args = strtok_fnc(buff, " ");
    free(buff);
    if (!args)
        return (res);
    if (check_cmd(args) != 0)
    {
        *ret = 2;
        free_args(args, args);
        return (*ret);
    }
    start = args;
    for (i = 0; args[i]; i++)
    {
        if (ncmp(args[i], ";", 1) == 0)
        {
            free(args[i]);
            args[i] = NULL;
            res = arg_call(args, start, ret);
            args = &args[++i];
            i = 0;
        }
    }
    if (args)
        res = arg_call(args, start, ret);
    free(start);
    return (res);
}

/**
 * exec_cmd - executes cmd
 * @args: array of args
 * @start: points to beginning of arg
 * @ret: return value
 * Return: ret of cmd
 */
int exec_cmd(char **args, char **start, int *ret)
{
    int i, res;
    int (*cmd)(char **args, char **start);

    cmd = getcmd_builtin(args[0]);

    if (cmd)
    {
        res = cmd(args + 1, start);
        if (res != EXIT)
            *ret = res;
    }
    else
    {
        *ret = _exec(args, start);
        res = *ret;
    }
    hist++;

    for (i = 0; args[i]; i++)
        free(args[i]);
    return (res);
}

/**
 * check_cmd - checks for operators
 * @args: array of args
 * Return: 0 on success, -2 on error
 */
int check_cmd(char **args)
{
    char *current, *fol;
    size_t i;

    for (i = 0; args[i]; i++)
    {
        current = args[i];
        if (current[0] == ';' || current[0] == '&'
            || current[0] == '|')
        {
            if (i == 0 || current[1] == ';')
                return (create_err(&args[i], 2));
            fol = args[i + 1];
            if (fol && (fol[0] == ';' || fol[0] == '&'
                || fol[0] == '|'))
                return (create_err(&args[i + 1], 2));
        }
    }
    return (0);
}

/**
 * arg_call - splits operators from cmd
 * @args: array of args
 * @start: points to beginning of args
 * @ret: return value
 * Return: ret
 */
int arg_call(char **args, char **start, int *ret)
{
    int i, res;

    if (!args[0])
        return (*ret);
    for (i = 0; args[i]; i++)
    {
        if (ncmp(args[i], "||", 2) == 0)
        {
            free(args[i]);
            args[i] = NULL;
            args = alias_rep(args);
            res = exec_cmd(args, start, ret);
            if (*ret != 0)
            {
                args = &args[++i];
                i = 0;
            }
            else
            {
                for (i++; args[i]; i++)
                    free(args[i]);
                return (res);
            }
        }
        else if (ncmp(args[i], "&&", 2) == 0)
        {
            free(args[i]);
            args[i] = NULL;
            args = alias_rep(args);
            res = exec_cmd(args, start, ret);
            if (*ret == 0)
            {
                args = &args[++i];
                i = 0;
            }
            else
            {
                for (i++; args[i]; i++)
                    free(args[i]);
                return (res);
            }
        }
    }
    args = alias_rep(args);
    res = exec_cmd(args, start, ret);
    return (res);
}