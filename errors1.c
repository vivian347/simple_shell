#include "shell.h"

char *e_env(char **arg);
char *e_1(char **arg);
char *e_2_exit(char **arg);
char *e_2_cd(char **arg);
char *e_2_syntax(char **arg);

/**
 * e_env - creates err messages for shell env errors
 * @arg: arguments passed to commands
 *
 * Return: error str
 */

char *e_env(char **arg)
{
	char *err, *hist_str = itoa_fnc(hist);
	int length;

	if (!hist_str)
		return (NULL);

	arg--;
	length = get_len(name) + get_len(hist_str) _ get_len(arg[0]) + 45;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	cpy_str(err, name);
	cat_str(err, ": ");
	cat_str(err, hist_str);
	cat_str(err, ": ");
	cat_str(err, arg[0]);
	cat_str(err, ": Cannot add/remove from environment\n");

	free(hist_str);
	return (err);
}

/**
 * e_1 - err messages for alias errors
 * @arg: argument passed to command
 *
 * Return: error string
 */

char *e_1(char **arg)
{
	char *err;
	int length;

	length = get_len(name) + get_len(arg[0]) + 13;
	err = malloc(sizeof(char) * (length + 1));
	if (err == NULL)
	{
		return (NULL);
	}
	cpy_str(err, "alias: ");
	cat_str(err, arg[0]);
	cat_str(err, " not found\n");
	return (err);
}

/**
 * e_2_exit - err messages for exit errors
 * @arg: argument passed to command
 *
 * Return: error string
 */

char *e_2_exit(char **arg)
{
	char *err, *hist_str = itoa_fnc(hist);
	int length;

	if (!hist_str)
		return (NULL);
	length = get_len(name) + get_len(hist_str) + get_len(arg[0]) + 27;
	err = malloc(sizeof(char) * (length + 1));

	if (err == NULL)
	{
		free(hist_str);
		return (NULL);
	}

	cpy_str(err, name);
	cat_str(err, ": ");
	cat_str(err, hist_str);
	cat_str(err, ": exit: Illegal number: ");
	cat_str(err, arg[0]);
	cat_str(err, "\n");

	free(hist_str);
	return (err);
}

/**
 * e_2_cd - error msg for cd errors
 * @arg: arg passed to command
 *
 * Return: error string
 */

char *e_2_cd(char **arg)
{
	char *err, *hist_str = itoa_fnc(hist);
	int len;

	if (!hist_str)
	{
		return (NULL);
	}

	if (arg[0][0] == '-')
	{
		arg[0][2] = '\0';
	}
	len = get_len(name) + get_len(hist_str) + get_len(arg[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	cpy_str(err, name);
	cat_str(err, ": ");
	cat_str(err, hist_str);
	if (arg[0][0] == '-')
		cat_str(err, ": cd: Invalid option ");
	else
		cat_str(err, ": cd: can't cd to ");
	cat_str(err, arg[0]);
	cat_str(err, "\n");

	free(hist_str);
	return (NULL);
}

/**
 * e_2_syntax - err msg for syntax errors
 * @arg: arg passed to command
 *
 * Return: error string
 */
char *e_2_syntax(char **arg)
{
	char *err, *hist_str = itoa_fnc(hist);
	int len;

	if (!hist_str)
	{
		return (NULL);
	}

	len = get_len(name) + get_len(hist_str) + get_len(arg[0]) + 33;
	err = malloc(sizeof(char) * (len + 1));

	if (!err)
	{
		free(hist_str);
		return (NULL);
	}
	cpy_str(err, name);
	cat_str(err, ": ");
	cat_str(err, hist_str);
	cat_str(err, ": Synatx error: \n");
	cat_str(err, arg[0]);
	cat_str(err, "\"unexpected\n");

	free(hist_str);
	return (err);
}
