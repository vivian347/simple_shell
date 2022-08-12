#include "shell.h"

char **getenv_fnc(const char *env_var);
char **env_cpy(void);
void free_env(void);

/**
 * getenv_fnc - Gets env var from PATH
 * @env_var:env var to get
 * Return: pointer to env var, NULL if absent
 */
char **getenv_fnc(const char *env_var)
{
	int len, i;

	len = get_len(env_var);
	for (i = 0; environ[i]; i++)
	{
		if (ncmp(env_var, environ[i], len) == 0)
			return (&environ[i]);
	}
	return (NULL);
}

/**
 * free_env - free env cpy
 * Return: void
 */
void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * env_cpy - copies env
 * Return: pointer to copy on success,
 * on error NULL is returned
 */
char **env_cpy(void)
{
	int i;
	char **env_new;
	size_t n;

	for (n = 0; environ[n]; n++)
		;
	env_new = malloc(sizeof(char *) * (n + 1));
	if (!env_new)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		env_new[i] = malloc(get_len(environ[i]) + 1);
		if (!env_new[i])
		{
			for (i--; i >= 0; i--)
			free(env_new[i]);
			free(env_new);
			return (NULL);
		}
		cpy_str(env_new[i], environ[i]);
	}
	env_new[i] = NULL;
	return (env_new);
}
