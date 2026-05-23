#include "shell.h"

/**
 * print_general_help - print list of builtins
 */
static void print_general_help(void)
{
	printf("hsh, simple shell.\n");
	printf("Builtin commands:\n");
	printf("  exit [n]      Exit the shell.\n");
	printf("  env           Print the environment.\n");
	printf("  cd [dir]      Change directory.\n");
	printf("  setenv VAR V  Set environment variable.\n");
	printf("  unsetenv VAR  Unset environment variable.\n");
	printf("  alias         Define or print aliases.\n");
	printf("  history       Show command history.\n");
	printf("  help [cmd]    Show help for a command.\n");
}

/**
 * print_help_topic - print help for specific topic
 * @topic: name
 * Return: 0 if found, 1 if not
 */
static int print_help_topic(const char *topic)
{
	if (strcmp(topic, "exit") == 0)
		printf("exit: exit [n]\n    Exit the shell with status n.\n");
	else if (strcmp(topic, "env") == 0)
		printf("env: env\n    Print the environment.\n");
	else if (strcmp(topic, "cd") == 0)
		printf("cd: cd [dir]\n    Change current directory.\n");
	else if (strcmp(topic, "setenv") == 0)
		printf("setenv: setenv VAR VALUE\n    Set environment variable.\n");
	else if (strcmp(topic, "unsetenv") == 0)
		printf("unsetenv: unsetenv VAR\n    Remove environment variable.\n");
	else if (strcmp(topic, "alias") == 0)
		printf("alias: alias [name=value]\n    Define or print aliases.\n");
	else if (strcmp(topic, "history") == 0)
		printf("history: history\n    Display command history.\n");
	else if (strcmp(topic, "help") == 0)
		printf("help: help [command]\n    Display info about builtins.\n");
	else
		return (1);
	return (0);
}

/**
 * builtin_help - help builtin
 * @args: args
 * Return: 0 on success
 */
int builtin_help(char **args)
{
	if (!args[1])
	{
		print_general_help();
		return (0);
	}
	if (print_help_topic(args[1]) != 0)
	{
		fprintf(stderr, "help: no help topics match '%s'\n", args[1]);
		return (1);
	}
	return (0);
}
