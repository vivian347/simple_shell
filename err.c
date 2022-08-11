#include "shell.h"

int dig_len(int n);
char *itoa_fnc(int n);
int create_err(char **arg, int error);

/**
 * dig_len - counts digit length of a number
 * @n: number to measure
 *
 * Return: length
 */

int dig_len(int n)
{
	unsigned int num;
	int len = 1;

	if (n < 0)
	{
		len++;
		num = n * -1;
	}
	else
	{
		num = n;
	}
	while (num > 9)
	{
		len++;
		num /= 10;
	}
	return (len);
}

/**
 * itoa_fnc - converts integer to string
 * @n: integer
 *
 * Return: converted string
 */

char *itoa_fnc(int n)
{
	char *buf;
	int len = dig_len(n);
	unsigned int num;

	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	buf[len] = '\0';

	if (n < 0)
	{
		num = n * -1;
		buf[0] = '-';
	}
	else
		num = n;
	len--;
	do
	{
		buf[len] = (num % 10) + '0';
		num /= 10;
		len--;
	} while (num > 0);

	return (buf);
}

int create_err(char **arg, int error)
{
	char *err;

	switch (error)
	{
		case -1:
			err = e_env(arg);
			break;
		case 1:
			err = e_1(arg);
			break;
		case 2:
			if (*(arg[0] == 'e'))
				err = e_2_exit(++arg);
			else if (arg[0][0] == ';' || arg[0][0] == '&' || arg[0][0] == '|')
				err = e_2_syntax(arg);
			else
				err = e_2_cd(arg);
			break;
		case 126:
			err = e_126(arg);
			break;
		case 127:
			err = e_127(arg);
			break;
	}
	write(STDERR_FILENO, err, get_len(err));

	if (err)
		free(err);
	return (error);
}
