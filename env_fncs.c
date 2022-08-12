#include "shell.h"

int _env(char **args, char __attribute__((__unused__)) **start);
int _setenv(char **args, char __attribute__((__unused__)) **start);
int _unsetenv(char **args, char __attribute__((__unused__)) **start);

/**
 * _env - prints curr env
 * @args: array of args
 * @start: pointer to beginning of args
 * Return: 0 on success, -1 on failure
 */
int _env(char **args, char __attribute__((__unused__)) **start)
{
	char line_char = '\n';
	int i;

	if (!environ)
		return (-1);
	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], get_len(environ[i]));
		write(STDOUT_FILENO, &line_char, 1);
	}
	(void)args;
	return (0);
}

/**
 * _setenv - sets env var to the PATH
 * @args: array of args
 * @start: points to beginning of args
 * Return: 0 on success, -1 on error
 */
int _setenv(char **args, char __attribute__((__unused__)) **start)
{
	int i;
	char **env = NULL, **env_new, *val_new;
	size_t n;

	if (!args[0] || !args[1])
		return (create_err(args, -1));
	val_new = malloc(get_len(args[0]) + 1 + get_len(args[1]) + 1);
	if (!val_new)
		return (create_err(args, -1));
	cpy_str(val_new, args[0]);
	cat_str(val_new, "=");
	cat_str(val_new, args[1]);
	env = getenv_fnc(args[0]);
	if (env)
	{
		free(*env);
		*env = val_new;
		return (0);
	}
	for (n = 0; environ[n]; n++)
		;
	env_new = malloc(sizeof(char *) * (n + 2));
	if (!env_new)
	{
		free(val_new);
		return (create_err(args, -1));
	}
	for (i = 0; environ[i]; i++)
		env_new[i] = environ[i];
	free(environ);
	environ = env_new;
	environ[i] = val_new;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - removes env var from PATH
 * @args: array of args
 * @start: points to beginning of args
 * Return: 0 on success, -1 on error
 */
int _unsetenv(char **args, char __attribute__((__unused__)) **start)
{
	int i, j;
	char **env, **env_new;
	size_t n;

	if (!args[0])
		return (create_err(args, -1));
	env = getenv_fnc(args[0]);
	if (!env)
		return (0);
	for (n = 0; environ[n]; n++)
		;
	env_new = malloc(sizeof(char *) * n);
	if (!env_new)
		return (create_err(args, -1));
	for (i = 0, j = 0; environ[i]; i++)
	{
		if (*env == environ[i])
		{
			free(*env);
			continue;
			env_new[j] = environ[i];
			j++;
		}
		free(environ);
		environ = env_new;
		environ[n - 1] = NULL;
	}
	return (0);

}
