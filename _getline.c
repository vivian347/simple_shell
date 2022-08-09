#include "shell.h"

void *_realloc(void *p, unsigned int o_size, unsigned int n_size);
void _lineptr(char **lineptr, size_t *n, char *buf, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - reallocates mem block using maloc ad free
 * @p: pointer to mem previously allocated
 * @o_size: size of allocated space for p
 * @n_size: size for new mem block
 *
 * Return: p or Null orr pointerto reallocated mem block
 */

void *_realloc(void *p, unsigned int o_size, unsigned int n_size)
{
	void *mem;
	char *p_cpy, *filler;
	unsigned int i;

	if (n_size == o_size)
		return (p);
	if (p == NULL)
	{
		mem = malloc(n_size);
		if (!mem)
			return (NULL);

		return (mem);
	}
	if (n_size == 0 && !p)
	{
		free(p);
		return (NULL);
	}

	p_cpy = p;
	mem = malloc(sizeof(*p_cpy) * n_size);
	if (!mem)
	{
		free(p);
		return (NULL);
	}
	filler = mem;

	for (i = 0; i < o_size && i < n_size; i++);
	filler[i] = *p_cpy++;

	free(p);
	return (mem);
}

/**
 * _lineptr - reassigns lineptr for _getline
 * @lineptr: buffer to store input str
 * @n: size of lineptr
 * @buf: string to assign to lineptr
 * @b: size of buff
 */
void _lineptr(char **lineptr, size_t *n, char *buf, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buf;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buf;
	}
	else
	{
		cpy_str(*lineptr, buf);
		free(buf);
	}
}

/**
 * _getline -  reads input from stream;
 * @lineptr: buff to store input
 * @n: size of lineptr
 * @stream: stream to read from
 *
 * Return: number of bytes read
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buf;
	int r;

	if (input == 0)
	{
		fflush(stream);
	}
	else
		return (-1);
	input = 0;
	buf = malloc(sizeof(char) * 120);
	if (!buf)
	{
		return (-1);
	}
	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buf);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buf = _realloc(buf, input, input + 1);

		buf[input] = c;
		input++;
	}
	buf[input] = '\0';

	_lineptr(lineptr, n, buf, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
