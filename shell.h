#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

/**
 * struct alias_s - linked list for aliases
 * @name: alias name
 * @value: alias value
 * @next: next node
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/**
 * struct history_s - linked list for history
 * @command: command text
 * @num: history number
 * @next: next node
 */
typedef struct history_s
{
	char *command;
	int num;
	struct history_s *next;
} history_t;

extern alias_t *g_aliases;
extern history_t *g_history;
extern int g_hist_count;
extern int g_last_status;

void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args, char *program_name);
int handle_builtin(char **args);
void print_env(void);
char *find_path(char *command);
char *get_env(char *name);

int run_line(char *line, char *program_name);
char **split_by_str(char *line, const char *sep, int *count);
int run_logical(char *segment, char *program_name);
char *trim_spaces(char *s);

int builtin_alias(char **args);
alias_t *add_alias(const char *name, const char *value);
alias_t *find_alias(const char *name);
void free_aliases(void);
char *substitute_alias(char *line);

char *expand_variables(char *line);
void strip_comment(char *line);

int builtin_help(char **args);
int builtin_history(char **args);
void add_history(const char *cmd);
void free_history(void);

int run_file(const char *filename, char *program_name);

char *_strdup(const char *s);
int _strlen(const char *s);
int _atoi(const char *s);
char *_itoa(int n);

#endif
