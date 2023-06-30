#include "shell_.h"

void help_all_func(void);
void help_alias_func(void);
void help_cd_func(void);
void help_exit_func(void);
void help_help_func(void);


/**
 * help_all_func -displays a list of internal shell commands and provides instructions on
 * how to use them.
 */
void help_all_func(void)
{
	char *out_msg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
}


/**
 * help_alias_func - provides information about how to use the "alias" command in C.
 */
void help_alias_func(void)
{
	char *out_msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
}


/**
 * help_cd_func - provides information about the "cd" command in C.
 */
void help_cd_func(void)
{
	char *out_msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "after a change of directory.\n";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
}


/**
 * help_exit_func-  provides information about the "exit" command in a shell.
 */
void help_exit_func(void)
{
	char *out_msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = " exit 0.\n";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
}


/**
 *help_help_func-  displays information about the "help" command in a shell program.
 */
void help_help_func(void)
{
	char *out_msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
	out_msg = "builtin command.\n";
	write(STDOUT_FILENO, out_msg, strlen_func(out_msg));
}
