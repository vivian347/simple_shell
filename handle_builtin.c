#include "shell.h"

int exit_fn(char **args, char **start);
int _help(char **args, char __attribute__((__unused__)) **start);
int _cd(char **args, char __attribute__((__unused__)) **start);
int (*getcmd_builtin(char *cmd))(char **args, char **start);

/**
 * getcmd_builtin - gets and compares cmd with builtin
 * @cmd: cmd to compare
 * Return: pointer to builtin cmd
 */
int (*getcmd_builtin(char *cmd))(char **args, char **start)
{
    int i;
    builtin_t funcs[] = {
        {"exit", exit_fn},
        {"cd", _cd},
        {"help", _help},
        {"env", _env},
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {"alias", alias_shell},
        {NULL, NULL}
    };

    for (i = 0; funcs[i].name; i++)
    {
        if (cmp(funcs[i].name, cmd) == 0)
            break;
    }
    return (funcs[i].f);
}

/**
 * _cd - changes current dir
 * @args: array of args
 * @start: points to beginning of args
 * Return: 0 on success, -1 on error
 * and -2 if not dir
 */
int _cd(char **args, char __attribute__((__unused__)) **start)
{
    struct stat directory;
    char *pwd = NULL, *new_pwd = NULL;
    char **dir, *new_line = "\n";

    pwd = getcwd(pwd, 0);
    if (!pwd)
        return (-1);
    if (args[0])
    {
        if (*(args[0]) == '-' || cmp(args[0], "--") == 0)
        {
            if ((args[0][1] == '-' && args[0][2] == '\0') ||
                args[0][1] == '\0')
            {
                if (getenv_fnc("OLDPWD") != NULL)
                    (chdir(*getenv_fnc("OLDPWD") + 7));
            }
            else
            {
                free(pwd);
                return (create_err(args, 2));
            }
        }
        else
        {
            if (stat(args[0], &directory) == 0 && S_ISDIR(directory.st_mode)
                && ((directory.st_mode & S_IXUSR) != 0))
                chdir(args[0]);
            else
            {
                free(pwd);
                return (create_err(args, 2));
            }
        }
    }
    else
    {
        if (getenv_fnc("HOME") != NULL)
            chdir(*(getenv_fnc("HOME")) + 5);
    }
    new_pwd = getcwd(new_pwd, 0);
    if (!new_pwd)
        return (-1);
    dir = malloc(sizeof(char *) * 2);
    if (!dir)
        return (-1);
    dir[0] = "OLDPWD";
    dir[1] = new_pwd;
    if (_setenv(dir, dir) == -1)
        return (-1);
    if (args[0] && args[0][0] == '-' && args[0][1] != '-')
    {
        write(STDOUT_FILENO, new_pwd, get_len(new_pwd));
        write(STDOUT_FILENO, new_line, 1);
    }
    free(pwd);
    free(new_pwd);
    free(dir);
    return (0);
}

/**
 * _help - displays info on builtin cmds
 * @args: array of args
 * @start: points to beginning of args
 * Return: 0 on success, -1 on error
 */
int _help(char **args, char __attribute__((__unused__)) **start)
{
    if (!args[0])
        h_all();
    else if (cmp(args[0], "alias") == 0)
        h_alias();
    else if (cmp(args[0], "cd") == 0)
        h_cd();
    else if (cmp(args[0], "exit") == 0)
        h_exit();
    else if (cmp(args[0], "help") == 0)
        h_help();
    else if (cmp(args[0], "env") == 0)
        h_env();
    else if (cmp(args[0], "setenv") == 0)
        h_setenv();
    else if (cmp(args[0], "unsetenv") == 0)
        h_unsetenv();
    else
        write(STDERR_FILENO, name, get_len(name));
    return (0);
}

/**
 * _exit - process terminates on call
 * @args: array of args
 * @start: beginnning of args
 * Return: status value on success
 * -2 on invalid exit value
 * -3 if no args are passed
 */
int exit_fn(char **args, char **start)
{
    int i, int_len = 10;
    unsigned int val = 0;
    unsigned int max_val = 1 << (sizeof(int) * 8 - 1);

    if (args[0])
    {
        if (args[0][0] == '+')
        {
            i = 1;
            int_len++;
        }
        for (; args[0][i]; i++)
        {
            if (i <= int_len && args[0][i] >= '0'
                && args[0][i] <= '9')
                val = (val * 10) + (args[0][i] - '0');
            else
                return (create_err(--args, 2));
        }
    }
    else
    {
        return (-3);
    }
    if (val > max_val - 1)
        return (create_err(--args, 2));
    args -= 1;
    free_args(args, start);
    free_env();
    aliaslist_free(aliases);
    exit(val);
}