#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int x;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t get_line_func(char **lineptr, size_t *n, FILE *stream);
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **strtok_func(char *x, char *d);
char *get_path_func(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void collect_e_list(list_t *head);
char *itoa_func(int num);

/* Input Helpers */
void handle_line_func(char **line, ssize_t read);
void variable_repl_func(char **args, int *exe_ret);
char *get_parms(char *line, int *exe_ret);
int call_parms(char **args, char **front, int *exe_ret);
int run_parms(char **args, char **front, int *exe_ret);
int handle_parms(int *exe_ret);
int check_parms(char **args);
void collect_parms(char **args, char **front);
char **update_aliases(char **args);

/* String functions */
int strlen_func(const char *s);
char *strcat_func(char *s2, const char *s1);
char *strncat_func(char *s2, const char *s1, size_t am);
char *strcpy_func(char *s2, const char *s1);
char *strchr_func(char *stt, char ch);
int strspn_func(char *stt, char *d);
int strcmp_func(char *stt1, char *stt2);
int strncmp_func(const char *stt1, const char *stt2, size_t am);

/* Builtins */
int (*get_built_in_func(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_env_func(char **args, char __attribute__((__unused__)) **front);
int shell_set_env_func(char **args, char __attribute__((__unused__)) **front);
int shell_unset_env_func(char **args, char __attribute__((__unused__)) **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_alias(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **cp_env_func(void);
void collect_env(void);
char **get_env(const char *var);

/* Error Handling */
int generate_error(char **args, int err);
char *err_env_func(char **args);
char *err_1(char **args);
char *err_2_exit(char **args);
char *err_2_cd(char **args);
char *err_2_syntax(char **args);
char *err_126(char **args);
char *err_127(char **args);

/* Linkedlist Helpers */
alias_t *end_alias(alias_t **head, char *name, char *value);
void collect_ls_alias(alias_t *head);
list_t *end_node(list_t **head, char *dir);
void collect_e_list(list_t *head);

void help_all_func(void);
void help_alias_func(void);
void help_cd_func(void);
void help_exit_func(void);
void help_help_func(void);
void help_env(void);
void help_set_env(void);
void help_unset_env(void);
void help_hist(void);

int proc_func(char *f_path, int *exe_e);
#endif /* _SHELL_H_ */
