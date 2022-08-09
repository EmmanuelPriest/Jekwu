#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

void read_cmd(void);
void tokenizer(char *buf, char *buf_cpy);
void exec_cmd(char **argv);

/* Double pointer to an array of strings known as "environment" */
extern char **environ;

/**
* struct data - struct that contains all neccesary dat at runtime
* @av: argument vector
* @input: user command line input
* @args: command line tokens
* @stat: the shell last status
* @count: counting of lines
* @_environ: environment variable
* @pid: the shell process identifier
*/
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int stat;
	int count;
	char **_environ;
	char *pid;
} data_shell;

/**
* struct sep_list_s - singly linked list
* @sep: ; | &
* @next: next node
*
* Description: singly linked list for storing separators
*/
typedef struct sep_list_s
{
	char sep;
	struct sep_list_s *next;
} sep_list;

/**
* struct line_list_s - singly linked list
* @next: next node
* @line: command line
*
* Description: singly linked list for storing command lines
*/
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
* struct r_var_list - singly linked list
* @length_var: variable length
* @value: value of the variable
* @length_val: value length
* @next: next node
*
* Description: singly linked list for storing variables
*/
typedef struct r_var_list
{
	int length_var;
	char *value;
	int length_val;
	struct r_var_list *next;
} r_var;

/**
* struct inbuilt_s - inbuilt struct for command arguments
* @name: name of inbuilt commands like cd, exit, env
* @f: pointer to a function
*/
typedef struct inbuilt_s
{
	char *name;
	int (*f)(data_shell *datash);
} inbuilt_t;

/* lists.c */
sep_list *add_sep_node_end(sep_list **head, char separ);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* lists2.c */
r_var *add_rvar_node(r_var **head, int lengthVar, char *var, int lengthVal);
void free_rvar_list(r_var **head);

/* string.c functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* memory.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* string1.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* string2.c */
void rev_string(char *s);

/* syntaxError.c */
int repeatedChar(char *input, int index);
int error_sep_op(char *input, int index, char last);
int firstChar(char *input, int *n);
void printSyntaxError(data_shell *datash, char *input, int index, int bool);
int checkSyntaxError(data_shell *datash, char *input);

/* sh_loop.c */
char *withoutComment(char *input);
void shellLoop(data_shell *datash);

/* readLine.c */
char *readLine(int *i_eof);

/* sh_split.c */
char *swapChar(char *input, int bool);
void addNodes(sep_list **head_s, line_list **head_l, char *input);
void goNext(sep_list **list_s, line_list **list_l, data_shell *datash);
int splitCmd(data_shell *datash, char *input);
char **splitLine(char *input);

/* repVar.c */
void check_env(r_var **head, char *input, data_shell *data);
int checkVars(r_var **head, char *input, char *st, data_shell *data);
char *replacedInput(r_var **head, char *input, char *new_input, int newLength);
char *repVar(char *input, data_shell *datash);

/* getLine.c */
void bringLine(char **lineptr, size_t *n, char *buffer, size_t m);
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);

/* executeLine.c */
int executeLine(data_shell *datash);

/* executeCmd.c */
int is_cdir(char *path, int *index);
char *_which(char *cmd, char **_environ);
int _executable(data_shell *datash);
int checkErrorCmd(char *dir, data_shell *datash);
int executeCmd(data_shell *datash);

/* _env1.c */
int cmp_env_name(const char *nenv, const char *name)
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

/* _env2.c */
char *copyInfo(char *name, char *value);
void setEnv(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* cd.c */
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_former(data_shell *datash);
void cd_home(data_shell *datash);

/* cd_shell.c */
int cd_shell(data_shell *datash);

/* getInbuilt.c */
int (*getInbuilt(char *cmd))(data_shell *datash);

/* _exit.c */
int exitShell(data_shell *datash);

/* _stdlib.c */
int getLength(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* _error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *errorNotFound(data_shell *datash);
char *errorExitShell(data_shell *datash);

/* _error2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *errorSyntax(char **args);
char *errorPermit(char **args);
char *error_path_126(data_shell *datash);

/* getError.c */
int getError(data_shell *datash, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* _help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* _help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* getHelp.c */
int getHelp(data_shell *datash);

/* main.c */
int main(int ac, char **av);
void setData(data_shell *datash, char **av);
void freeData(data_shell *datash);
#endif
