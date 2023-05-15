#ifndef SHELL_H
#define SHELL_H

/*header files*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fnctl.h>
#include <stdarg.h>
#include <stdarg.h>

/*global variables to environment*/
extern char **environ;

/*macros*/
#define BUFSIZE 1024
#define PRINT(c) (write(STDIN_FILENO, c, _strlen(c)))
#define DELIMITER " \a\n\t\r"
#define TOK_SIZE 64

/**
 * struct shell_data - Struct that holdS Global Data to run simple shell.
 * @line: the line input of the user
 * @av: arg vector
 * @args: tokenised parts of line
 * @env: environment data variables
 * @pid: child process ID
 * @count: counts the inputed commands
 * @status: the final statuts of the last shell run
 *
 * Descprition: this structure contains all required data and variables
 * to run and manage the simple shell program.
 */
typedef struct shell_data
{
	char *line;
	char *av;
	char **args;
	char **env;
	char *pid;
	int count;
	int status;
} sh_dt;

/**
 * struct builtin - Helps to manage builtin functions.
 * @cmd: the command line in form of string.
 * @f: function associated with the shell data.
 * Description: this structure id made to manage builtin commands.
 */

typedef struct builtin
{
	char *cmd;
	int (*f)(sh_dt *data);
} blt_cmd;

/**
 * struct command_strore - single linked list for storage
 * @c_line: command line entered
 * @next: next node
 *
 * Description: this linked list aimed to store command line
 */

typedef struct command_strore
{
	char *c_line;
	struct command_store *next;
} cmd_st;

/**
 * struct list_var - linled list that stores variables
 * @var_val: variable value;
 * @var_len: lenth of variable
 * @val_len: lenth of value of variable
 * @next: next node
 *
 * Description: this list_var linked list stores all about variables
 */
typedef struct list_var
{
	char *var_val;
	int var_len;
	int val_len;
	struct list_var *next
} l_v;

/**
 * struct list_separators - struct node of list separators
 * @sep: the separators in shell i.e: ; | &
 * @next: next node;
 * Description: this singly linked list stores separators
 */
typedef struct list_separators
{
	char sep;
	struct list_separators *next;
} list_sep;



/*prototypes*/

/*memory managements prototypes*/
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_lv(l_v **head);

/*string managements prototypes*/
int _strlen(char *s);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
int _atoi(char *s);
int _isdigit(int c);

/*main_helpers*/
void sigInt(int sigHandler);
void data_init(char **av, sh_dt *data);
char *get_input(int *ret);
char *hash_hand(char *str);

/*syntax_err*/
int count_repeats(char *s, int start);
int get_err_sep(char *str, int i, char j);
void synt_err_print(sh_dt *data, char *str, int i, int bool);
int idx_char(char *str, int *idx);
int err_synt_checker(sh_dt *data, char *str);

/*getline*/
int _getline(char *cmd);

/*tools & more_tools*/
int _sprintf(char *str, const char *format, ...);
int _intlen(int num);
char *_itoa(unsigned int n);
void arr_rev(char *arr, int len);

/*add node*/
l_v *add_lv_n(lv **head, int lvr, int *v, int lvl);

#endif
