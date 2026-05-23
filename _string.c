#include "shell.h"

/**
 * _strdup - duplicate a string
 * @s: string
 * Return: new string or NULL
 */
char *_strdup(const char *s)
{
	int i, len = 0;
	char *p;

	if (!s)
		return (NULL);
	while (s[len])
		len++;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	for (i = 0; i <= len; i++)
		p[i] = s[i];
	return (p);
}

/**
 * _strlen - string length
 * @s: string
 * Return: length
 */
int _strlen(const char *s)
{
	int n = 0;

	if (!s)
		return (0);
	while (s[n])
		n++;
	return (n);
}

/**
 * _atoi - convert string to int
 * @s: string
 * Return: integer value
 */
int _atoi(const char *s)
{
	int n = 0, sign = 1;

	if (!s)
		return (0);
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n * sign);
}

/**
 * _itoa - convert int to string
 * @n: integer
 * Return: new string
 */
char *_itoa(int n)
{
	char buf[16];
	int i = 0, neg = 0;
	char *res;

	if (n == 0)
		return (_strdup("0"));
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	while (n > 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		buf[i++] = '-';
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	res[i] = '\0';
	i--;
	for (; i >= 0; i--)
		res[i] = buf[(neg ? i : i)];
	{
		int j, k;
		for (j = 0, k = _strlen(buf) - 1; j < _strlen(buf); j++, k--)
			res[j] = buf[k];
		res[_strlen(buf)] = '\0';
	}
	return (res);
}
