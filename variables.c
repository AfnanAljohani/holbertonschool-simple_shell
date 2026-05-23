#include "shell.h"

/**
 * get_var_value - get value of a variable
 * @name: variable name without dollar
 * Return: allocated string
 */
static char *get_var_value(const char *name)
{
	char *v;

	if (strcmp(name, "?") == 0)
		return (_itoa(g_last_status));
	if (strcmp(name, "$") == 0)
		return (_itoa(getpid()));
	v = get_env((char *)name);
	if (v)
		return (_strdup(v));
	return (_strdup(""));
}

/**
 * read_name - read variable name
 * @p: pointer after dollar sign
 * @name: buffer
 * Return: chars consumed
 */
static int read_name(const char *p, char *name)
{
	int i = 0;

	if (*p == '?' || *p == '$')
	{
		name[0] = *p;
		name[1] = '\0';
		return (1);
	}
	while (p[i] && p[i] != ' ' && p[i] != 9 && p[i] != '$' &&
	       p[i] != '=' && p[i] != ';' && p[i] != '&' && p[i] != '|')
	{
		name[i] = p[i];
		i++;
	}
	name[i] = '\0';
	return (i);
}

/**
 * expand_variables - expand variables in line
 * @line: input
 * Return: new allocated line
 */
char *expand_variables(char *line)
{
	char *res, *val, name[256];
	int i = 0, j = 0, k, consumed;
	size_t cap = 1024;

	res = malloc(cap);
	if (!res)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] &&
		    line[i + 1] != ' ' && line[i + 1] != 9)
		{
			consumed = read_name(&line[i + 1], name);
			val = get_var_value(name);
			while ((size_t)(j + _strlen(val) + 2) >= cap)
			{
				cap *= 2;
				res = realloc(res, cap);
			}
			for (k = 0; val[k]; k++)
				res[j++] = val[k];
			free(val);
			i += consumed + 1;
		}
		else
		{
			res[j++] = line[i++];
			if ((size_t)(j + 2) >= cap)
			{
				cap *= 2;
				res = realloc(res, cap);
			}
		}
	}
	res[j] = '\0';
	return (res);
}
