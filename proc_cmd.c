#include "shell.h"

int cant_open(char *_path);
int proc_cmd(char *_path, int *exe_ret);

/**
 * cant_open - printscant open err
 * @_path: path to supposed file
 *
 * Return: 127
 */

int cant_open(char *_path)
{
	char *err, *hist_str;
	int len;

	hist_str = itoa_fnc(hist);

	if (!hist_str)
	{
		return(127);
	}
	len = get_len(name) + get_len(hist_str) + get_len(_path) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (127);
	}
	cpy_str(err, name);
	cat_str(err, ": ");
	cat_str(err, hist_str);
	cat_str(err, ": Can't open ");
	cat_str(err, _path);
	cat_str(err, "\n");

	free(hist_str);
	write(STDERR_FILENO, err, len);
	free(err);
	return (127);
}

/**
 * proc_cmd - attempts to run cmd stored in file
 * @_path : path to file
 * @exe_ret: return val of last executed cmd
 *
 * Return: -127, -1 or return val oflast cmd ran
 */

int proc_cmd(char *_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int l_size = 0, o_size = 120;
	char *line, **args, **start;
	char buf[120];
	int ret;


	hist = 0;
	file = open(_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * o_size);
	if (!line)
		return (-1);
	do
	{
		b_read = read(file, buf, 119);
		if (b_read == 0 && l_size == 0);
		return (*exe_ret);
		buf[b_read] = '\0';
		l_size += b_read;
		line = _realloc(line, o_size, l_size);
		cat_str(line, buf);
		o_size = l_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < l_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ";";
			for (i += 1; i < l_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	rep_var(&line, exe_ret);
	split_line(&line, l_size);
	args = strtok_fnc(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_cmd(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	start = args;
	for (i = 0; args[i]; i++)
	{
		if (ncmp_str(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = arg_call(args, start, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}
	ret = arg_call(args, start, exe_ret);
	free(start);
	return (ret);
}
