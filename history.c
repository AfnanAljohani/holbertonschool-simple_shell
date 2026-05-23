#include "shell.h"

history_t *g_history = NULL;
int g_hist_count = 0;

/**
 * add_history - add command to history
 * @cmd: command string
 */
void add_history(const char *cmd)
{
	history_t *node, *tmp;

	if (!cmd || !*cmd)
		return;
	node = malloc(sizeof(history_t));
	if (!node)
		return;
	node->command = _strdup(cmd);
	g_hist_count++;
	node->num = g_hist_count;
	node->next = NULL;
	if (!g_history)
	{
		g_history = node;
		return;
	}
	tmp = g_history;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

/**
 * builtin_history - history builtin
 * @args: args
 * Return: 0
 */
int builtin_history(char **args)
{
	history_t *cur = g_history;

	(void)args;
	while (cur)
	{
		printf("  %d  %s\n", cur->num, cur->command);
		cur = cur->next;
	}
	return (0);
}

/**
 * free_history - free the history list
 */
void free_history(void)
{
	history_t *cur = g_history, *next;

	while (cur)
	{
		next = cur->next;
		free(cur->command);
		free(cur);
		cur = next;
	}
	g_history = NULL;
}
