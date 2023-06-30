#include "shell_.h"

void help_env(void);
void help_set_env(void);
void help_unset_env(void);
void help_hist(void);


/**
 *  "help_env" prints the current environment.
 */
void help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, strlen_func(msg));
}


/**
 *  "help_set_env" provides information on how to use the "setenv" command in C to
 * initialize or modify environment variables.
 */
void help_set_env(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, strlen_func(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, strlen_func(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, strlen_func(msg));
}


/**
 *  `help_unset_env` provides a description of the `unsetenv` command and its usage.
 */
void help_unset_env(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, strlen_func(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, strlen_func(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, strlen_func(msg));
}
