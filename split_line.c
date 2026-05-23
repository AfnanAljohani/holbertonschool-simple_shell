#include "shell.h"
static int count_words(char *line)
{
	int count = 0, in_word = 0;

	while (*line)
	{
		if (*line != 32 && *line != 9 && *line != 10)
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		line++;
	}
	return (count);
}

char **split_line(char *line)
{
	char **tokens;
	char *copy, *tok;
	int count, i = 0;

	if (!line)
		return (NULL);
	count = count_words(line);
	tokens = malloc(sizeof(char *) * (count + 2));
	if (!tokens)
		return (NULL);
	copy = _strdup(line);
	if (!copy)
	{
		free(tokens);
		return (NULL);
	}
	tok = strtok(copy, " \t\n");
	while (tok)
	{
		tokens[i++] = _strdup(tok);
		tok = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	free(copy);
	return (tokens);
}
