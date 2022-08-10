#include "shell.h"

char *_loc(char *cmd);
char *fill_path(char *path);
list_t *get_path(char *path);

/**
 * _loc - locates command in path
 * @cmd: command to locate
 *
 * Return: pathname of cmd or NULL
 */

char *_loc(char *cmd)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat buf;

	path = getenv_fnc("PATH");
	if (!path || !(*path))
		return (NULL);
	dirs = get_path(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(get_len(dirs->dir) + get_len(cmd) + 2);
		if (!temp)
			return (NULL);

		cpy_str(temp, dirs->dir);
		cat_str(temp, "/");
		cat_str(temp, cmd);
		if (stat(temp, &buf) == 0)
		{
			free_list(head);
			return (temp);
		}
		dirs = dirs->next;
		free(temp);
	}
	free_list(head);

	return (NULL);
}

/**
 * fill_path - copies ath and replace leading colon with cwd
 * @path: colon-sep list of dir
 *
 * Return: path
 */

char *fill_path(char *path)
{
	int i, len = 0;
	char *path_cpy, *pwd;

	pwd = (*getenv_fnc("PWD")) + 4;
	for (i = 0; path[i]; i++);
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i = 0 || path[i +1] == '\0')
				len = get_len(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_cpy = malloc(sizeof(char) * (len + 1));
	if (!path_cpy)
		return (NULL);
	path_cpy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] ==':')
		{
			if (i == 0)
			{
				cat_str(path_cpy, pwd);
				cat_str(path_cpy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				cat_str(path_cpy, ":");
				cat_str(path_cpy, pwd);
			}
			else
				cat_str(path_cpy, ":");
		}
		else
		{
			ncat_str(path_cpy, &path[i], 1);
		}
	}
	return (path_cpy);
}

/**
 * get_path - tokenize colon-sep directories into a linked list
 * @path: colon-sep list of directories
 *
 * Return: pointer to initialize linkedlist
 */

list_t *get_path(get_path)
{
	int i;
	char **dirs, *path_cpy;
	list_t *head = NULL;

	path_cpy = fill_path(path);
	if (!path_cpy)
		return (NULL);
	for (i = 0; dirs[i]; i++)
	{
		if (endnode_add(&head, dirs[i]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}
	free(dirs);

	return(head);
}
