#include "shell.h"

/**
 * substitute_alias - replace alias name at start of line with value
 * @line: input line
 * Return: new allocated line (or copy if no alias)
 */
char *substitute_alias(char *line)
{
	char *space, *word, *result, *rest;
	alias_t *node;
	int wlen, total;

	if (!line || !*line)
		return (_strdup(line ? line : ""));
	space = line;
	while (*space && *space != ' ' && *space != '\t')
		space++;
	wlen = space - line;
	word = malloc(wlen + 1);
	if (!word)
		return (_strdup(line));
	strncpy(word, line, wlen);
	word[wlen] = '\0';
	node = find_alias(word);
	free(word);
	if (!node)
		return (_strdup(line));
	rest = space;
	total = _strlen(node->value) + _strlen(rest) + 1;
	result = malloc(total);
	if (!result)
		return (_strdup(line));
	strcpy(result, node->value);
	strcat(result, rest);
	return (result);
}
