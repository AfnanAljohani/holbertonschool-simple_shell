#include "shell.h"

int g_last_status = 0;

/**
 * print_env - print environment variables
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * builtin_setenv - set an environment variable
 * @args: arguments
 * Return: 1 if handled, 0 otherwise
 */
static int builtin_setenv(char **args)
{
	if (!args[1] || !args[2])
	{
		fprintf(stderr, "setenv: usage: setenv VAR VALUE\n");
		g_last_status = 2;
		return (1);
	}
	setenv(args[1], args[2], 1);
	g_last_status = 0;
	return (1);
}

/**
 * builtin_unsetenv - unset an environment variable
 * @args: arguments
 * Return: 1 if handled
 */
static int builtin_unsetenv(char **args)
{
	if (!args[1])
	{
		fprintf(stderr, "unsetenv: usage: unsetenv VAR\n");
		g_last_status = 2;
		return (1);
	}
	unsetenv(args[1]);
	g_last_status = 0;
	return (1);
}

/**
 * builtin_cd - change directory
 * @args: arguments
 * Return: 1
 */
static int builtin_cd(char **args)
{
	char *target, cwd[1024];
	char *oldpwd = getcwd(cwd, sizeof(cwd));

	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		target = get_env("HOME");
		if (!target)
			return (1);
	}
	else if (strcmp(args[1], "-") == 0)
	{
		target = get_env("OLDPWD");
		if (!target)
			return (1);
		printf("%s\n", target);
	}
	else
		target = args[1];
	if (chdir(target) == -1)
	{
		fprintf(stderr, "cd: can't cd to %s\n", target);
		g_last_status = 2;
		return (1);
	}
	if (oldpwd)
		setenv("OLDPWD", oldpwd, 1);
	if (getcwd(cwd, sizeof(cwd)))
		setenv("PWD", cwd, 1);
	g_last_status = 0;
	return (1);
}

/**
 * handle_builtin - dispatch builtin commands
 * @args: argument array
 * Return: 1 if handled, 0 if not, 2 if exit
 */
int handle_builtin(char **args)
{
	if (!args[0])
		return (0);
	if (strcmp(args[0], "exit") == 0)
		return (2);
	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		g_last_status = 0;
		return (1);
	}
	if (strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	if (strcmp(args[0], "setenv") == 0)
		return (builtin_setenv(args));
	if (strcmp(args[0], "unsetenv") == 0)
		return (builtin_unsetenv(args));
	if (strcmp(args[0], "alias") == 0)
	{
		builtin_alias(args);
		g_last_status = 0;
		return (1);
	}
	if (strcmp(args[0], "help") == 0)
	{
		g_last_status = builtin_help(args);
		return (1);
	}
	if (strcmp(args[0], "history") == 0)
	{
		g_last_status = builtin_history(args);
		return (1);
	}
	return (0);
}
