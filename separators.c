#include "shell.h"

/**
 * trim_spaces - trim leading and trailing spaces
 * @s: string
 * Return: pointer to trimmed string
 */
char *trim_spaces(char *s)
{
	char *end;

	if (!s)
		return (s);
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\0')
		return (s);
	end = s + _strlen(s) - 1;
	while (end > s && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}
	return (s);
}

/**
 * split_by_str - split a line by a separator string
 * @line: input line
 * @sep: separator
 * @count: out count
 * Return: array of strings
 */
char **split_by_str(char *line, const char *sep, int *count)
{
	char **arr;
	char *p, *start;
	int n = 0, i = 0, slen;

	slen = _strlen(sep);
	p = line;
	while (*p)
	{
		if (strncmp(p, sep, slen) == 0)
		{
			n++;
			p += slen;
		}
		else
			p++;
	}
	arr = malloc(sizeof(char *) * (n + 2));
	if (!arr)
		return (NULL);
	start = line;
	p = line;
	while (*p)
	{
		if (strncmp(p, sep, slen) == 0)
		{
			*p = '\0';
			arr[i++] = _strdup(start);
			p += slen;
			start = p;
		}
		else
			p++;
	}
	arr[i++] = _strdup(start);
	arr[i] = NULL;
	*count = i;
	return (arr);
}
