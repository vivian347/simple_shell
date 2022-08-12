#include "shell.h"

char *get_val(char *env, int len);
void free_args(char **args, char **start);
char *_pid(void);
void rep_var(char **args, int *ret);

/**
 * get_val - gets value in env var
 * @env: env var to search for
 * @len: len of env var
 * Return: char*
 */
char *get_val(char *env, int len)
{
	char *var, *ptr, **addr, *rep = NULL;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	ncat_str(var, env, len);
	addr = getenv_fnc(var);
	free(var);
	if (addr)
	{
		ptr = *addr;
		while (*ptr != '=')
		ptr++;
		ptr++;
		rep = malloc(get_len(ptr) + 1);
		if (rep)
			cpy_str(rep, ptr);
	}
	return (rep);
}

/**
 * free_args - frees memory of args
 * @args: array of args
 * @start: beginning of args
 * Return: void
 */
void free_args(char **args, char **start)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
	free(args[i]);
	free(start);
}

/**
 * _pid - gets process id of curr procss
 * Return: on success process id is returned
 * on failure NULL
 */
char *_pid(void)
{
	size_t i = 0;
	ssize_t f;
	char *buff;

	f = open("proc/self/stat", O_RDONLY);
	if (f == -1)
	{
		perror("File cant be read!");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(f);
		return (NULL);
	}
	read(f, buff, 120);
	while (buff[i] != ' ')
		i++;
	buff[i] = '\0';

	close(f);
	return (buff);
}

/**
 * rep_var - replaces var
 * @args: array of args
 * @ret: pointer to ret val of exec cmd
 * Return: void
 */
void rep_var(char **args, int *ret)
{
	int len, i, j = 0;
	char *rep = NULL, *line = NULL, *line_new;

	line = *args;
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
		{
			if (line[i + 1] == '$')
			{
				rep = _pid();
				j = i + 2;
			}
			else if (line[i + 1] == '?')
			{
				rep = itoa_fnc(*ret);
				j = i + 2;
			}
			else if (line[i + 1])
			{
				for (j = i + 1; line[j] &&
					line[j] != '$' &&
					line[j] != ' '; j++)
					;
				len = j - (i + 1);
				rep = get_val(&line[i + 1], len);
			}
			line_new = malloc(i + get_len(rep) + get_len(&line[j]) + 1);
			if (!line)
				return;
			line_new[0] = '\0';
			ncat_str(line_new, line, j);
			if (rep)
			{
				cat_str(line_new, rep);
				free(rep);
				rep = NULL;
			}
			cat_str(line_new, &line[j]);
			free(line);
			*args = line_new;
			line = line_new;
			i = -1;
		}
	}
}
