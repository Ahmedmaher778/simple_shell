#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

/* read and write buffers */
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024

/* chaining command */
#define CMD_CHAIN	3
#define CMD_AND		2
#define CMD_OR		1
#define CMD_NORM	0

/* convert number */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

/* 1 if use getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;


/**
 * struct liststr - linked list
 * @num: number
 * @str: a string
 * @next: a node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - allowing uniform prototype for function pointer struct
 *@arg: a string
 *@argv: an array
 *@path: a string
 *@argc: a count of argument
 *@line_count: a count of error
 *@err_num: the error code
 *@linecount_flag: on count this line (on input)
 *@fname: file name
 *@env: local list of environ
 *@environ: modified copy of environ
 *@history: the history of node
 *@alias: the alias of node
 *@env_changed: when change environ
 *@status: status of last exec command
 *@cmd_buf: an address
 *@cmd_buf_type: CMD type || - && - ;
 *@readfd: the file directory
 *@histcount: the history line
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* pointer to cmd */
	int cmd_buf_type; /* CMD type || - && - ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - builtin string and the function is related
 *@type: flag
 *@func: is a function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c file */
void fork_cmd(info_t *);
int find_builtin(info_t *);
int hsh(info_t *, char **);
void find_cmd(info_t *);

/* path.c file */
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);

/* loophsh.c file */
int loophsh(char **);

/* err_string_functions.c file */
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
int _eputchar(char);
void _eputs(char *);

/* string_functions.c file */
char *_strcat(char *, char *);
char *starts_with(const char *, const char *);
int _strcmp(char *, char *);
int _strlen(char *);

/* string_functions2.c file */
int _putchar(char);
void _puts(char *);
char *_strdup(const char *);
char *_strcpy(char *, char *);

/* string_functions3.c file */
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

/* string_functions4.c file */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* memory_functions file */
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);

/* memory_functions2.c file */
int bfree(void **);

/* more_functions.c file */
int _atoi(char *);
int _isalpha(int);
int is_delim(char, char *);
int interactive(info_t *);

/* more_functions2.c file */
int _erratoi(char *);
int print_d(int, int);
void remove_comments(char *);
char *convert_number(long int, int, int);
void print_error(info_t *, char *);

/* builtin_emulators.c file */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

/* builtin_emulators2.c file */
int _myalias(info_t *);
int _myhistory(info_t *);

/* getline.c module file */
void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

/* info.c module file */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

/* env.c module file */
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);

/* env2.c module file */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

/* file_io_functions.c file */
int read_history(info_t *info);
int write_history(info_t *info);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

/* liststr.c module file */
void free_list(list_t **);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);

/* liststr2.c module file */
size_t print_list(const list_t *);
char **list_to_strings(list_t *);
size_t list_len(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);

/* chain.c file */
int replace_vars(info_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

#endif
