#include "shell.h"

char *e_126(char **arg);
char *e_127(char **arg);

/**
 * e_126 - error msg for permissions denied failures
 * @arg: arg passed tocommand
 *
 * Return: error string
 */

char *e_126(char **arg)
{
	char *err, *hist_str = itoa_fnc(hist);
	int len;

	if (!hist_str)
		return (NULL);
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
	cat_str(err, ": ");
	cat_str(err, arg[0]);
	cat_str(err, ": Permissions denied\n");

	free(hist_str);
	return (err);
}

/**
 * e_127- err msg for command not found failures
 * @arg: arg passed to command
 *
 * Return: error string
 */

char *e_127(char **arg)
{
	char *err, *hist_str = itoa_fnc(hist);
	int len;

	if (!hist_str)
		return (NULL);
	len = get_len(name) + get_len(hist_str) + get_len(arg[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));

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
	cat_str(err, ": Command not found\n");

	free(hist_str);
	return (NULL);
}
