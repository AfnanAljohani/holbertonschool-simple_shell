#include "shell.h"

alias_t *g_aliases = NULL;

/**
 * find_alias - find alias by name
 * @name: alias name
 * Return: node or NULL
 */
alias_t *find_alias(const char *name)
{
	alias_t *cur = g_aliases;

	while (cur)
	{
		if (strcmp(cur->name, name) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

/**
 * add_alias - add or update an alias
 * @name: alias name
 * @value: alias value
 * Return: pointer to node
 */
alias_t *add_alias(const char *name, const char *value)
{
	alias_t *node = find_alias(name);

	if (node)
	{
		free(node->value);
		node->value = _strdup(value);
		return (node);
	}
	node = malloc(sizeof(alias_t));
	if (!node)
		return (NULL);
	node->name = _strdup(name);
	node->value = _strdup(value);
	node->next = g_aliases;
	g_aliases = node;
	return (node);
}

/**
 * print_one_alias - print single alias line
 * @node: node
 */
static void print_one_alias(alias_t *node)
{
	printf("%s='%s'\n", node->name, node->value);
}

/**
 * builtin_alias - alias builtin
 * @args: args array
 * Return: 0
 */
int builtin_alias(char **args)
{
	int i;
	alias_t *cur;
	char *eq, *name, *val;

	if (!args[1])
	{
		cur = g_aliases;
		while (cur)
		{
			print_one_alias(cur);
			cur = cur->next;
		}
		return (0);
	}
	for (i = 1; args[i]; i++)
	{
		eq = strchr(args[i], '=');
		if (!eq)
		{
			cur = find_alias(args[i]);
			if (cur)
				print_one_alias(cur);
			else
				fprintf(stderr, "alias: %s not found\n", args[i]);
		}
		else
		{
			*eq = '\0';
			name = args[i];
			val = eq + 1;
			if (*val == '\'' || *val == '"')
			{
				val++;
				if (val[_strlen(val) - 1] == '\'' ||
				    val[_strlen(val) - 1] == '"')
					val[_strlen(val) - 1] = '\0';
			}
			add_alias(name, val);
		}
	}
	return (0);
}

/**
 * free_aliases - free alias list
 */
void free_aliases(void)
{
	alias_t *cur = g_aliases, *next;

	while (cur)
	{
		next = cur->next;
		free(cur->name);
		free(cur->value);
		free(cur);
		cur = next;
	}
	g_aliases = NULL;
}
