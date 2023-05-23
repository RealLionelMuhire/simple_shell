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
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/wait.h>

/*global variables to environment*/
extern char **environ;

/*macros*/
#define BUFSIZE 1024
#define PRINT(c) (write(STDIN_FILENO, c, _strlen(c)))
#define PRINT_ERR(c) (write(STDERR_FILENO, c, _strlen(c)))
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
	char **av;
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
 * struct command_store - single linked list for storage
 * @c_line: command line entered
 * @next: next node
 *
 * Description: this linked list aimed to store command line
 */

typedef struct command_store
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
	struct list_var *next;
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
} l_sep;



/*prototypes*/

/*memory managements prototypes*/
void *_memset(void *s, char b, size_t n);
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_lv(l_v **head);
int free_d(sh_dt *data);
void free_l_sep(l_sep **h);
void free_cmd_st(cmd_st **h);
void *_dp_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*string managements prototypes*/
int _strlen(char *s);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strtok(char *str,char *delim);
int _atoi(char *s);

/*main_helpers*/
void sigHandler(int sigNum);
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
char *replace_v(char *str, sh_dt *data);
int _isdigit(char *str);

/*add node*/
l_v *add_lv_n(l_v **head, int lvr, char *v, int lvl);
l_sep *add_l_sep_n(l_sep **head, char s);
cmd_st *add_cmd_st_n(cmd_st **h, char *cmd);
void add_sep_cmd_n(l_sep **h_s, cmd_st **h_c, char *str);

/*tok_cmd*/
char *ch_repl(char *str, int bool);
int cmd_tok(sh_dt *data, char *str);

/*executer*/
int exec_cmd(sh_dt *data);
int blt_cmd_h(sh_dt *data);

/*exec_helper*/
char loc_exec(char *cmd, char **env);

/*bultins and envirnonment*/
int (*_builtin(char *cmd))(sh_dt *data);
int compare_var(const char *env_var, const char *name);
char *get_env(char *name, char **env);
int handle_env(sh_dt *data);
int handle_exit(sh_dt *data);

/*environ*/
int handle_setenv(sh_dt *data);
char *create_copy(char *name, char *value);
int handle_unsetenv(sh_dt *data);

#endif
