#include "shell_.h"
int (*get_built_in_func(char *command))(char **pars, char **front);
int shell_exit(char **pars, char **front);
int shell_cd(char **pars, char __attribute__((__unused__)) **front);
int shell_help(char **pars, char __attribute__((__unused__)) **front);

/**
 *  "get_built_in_func" returns a pointer to a built-in function based on the given
 * command.
 * 
 * @param pars A pointer to an array of strings (char **pars) that represents the command line
 * arguments passed to .
 * @param front The "front" parameter is a pointer to a pointer to a string. It is used to keep track
 * of the front of the command string as it is being parsed.
 * 
 * @return  `get_built_in_func` returns a pointer to a function that takes two parameters:
 * `char **pars` and `char **front`.
 */
int (*get_built_in_func(char *command))(char **pars, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env_func },
		{ "setenv", shell_set_env_func },
		{ "unsetenv", shell_unset_env_func },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (strcmp_func(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}


/**
 *  `shell_exit` is used to exit the shell with a specified exit code.
 * 
 * @param pars A double pointer to a character array, which represents the command line arguments
 * passed to .
 * @param front The `front` parameter is a pointer to a pointer to a character array. It is used to
 * store the front part of the command line input, which is the part before the command itself.
 * 
 * @return the value of the variable "num".
 */
int shell_exit(char **pars, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (pars[0])
	{
		if (pars[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; pars[0][i]; i++)
		{
			if (i <= len_of_int && pars[0][i] >= '0' && pars[0][i] <= '9')
				num = (num * 10) + (pars[0][i] - '0');
			else
				return (generate_error(--pars, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (generate_error(--pars, 2));
	pars -= 1;
	collect_parms(pars, front);
	collect_env();
	collect_ls_alias(aliases);
	exit(num);
}


/**
 *  `shell_cd` is used to change the current working directory in a shell program.
 * 
 * @param pars An array of strings representing the command line arguments passed to the `shell_cd`
 * function. These arguments are used to determine the directory to change to.
 * @param __unused__ `__unused__` is an attribute that is used to indicate that a function parameter is
 * intentionally unused. It is typically used to suppress compiler warnings about unused variables. In
 * this case, `__unused__` is applied to the `front` parameter, indicating that it is not used in the `
 * 
 * @return an integer value.
 */
int shell_cd(char **pars, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (pars[0])
	{
		if (*(pars[0]) == '-' || strcmp_func(pars[0], "--") == 0)
		{
			if ((pars[0][1] == '-' && pars[0][2] == '\0') ||
					pars[0][1] == '\0')
			{
				if (get_env("OLDPWD") != NULL)
					(chdir(*get_env("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (generate_error(pars, 2));
			}
		}
		else
		{
			if (stat(pars[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(pars[0]);
			else
			{
				free(oldpwd);
				return (generate_error(pars, 2));
			}
		}
	}
	else
	{
		if (get_env("HOME") != NULL)
			chdir(*(get_env("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shell_set_env_func(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shell_set_env_func(dir_info, dir_info) == -1)
		return (-1);
	if (pars[0] && pars[0][0] == '-' && pars[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, strlen_func(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 *  `shell_help` provides help information for various shell commands.
 * 
 * @param pars An array of strings representing the command and its arguments.
 * @param __unused__ The `__unused__` attribute is used to indicate that a function parameter is
 * intentionally left unused. It is a way to suppress compiler warnings about unused variables. In this
 * case, the `__unused__` attribute is applied to the `front` parameter, indicating that it is not used
 * in the
 * 
 * @return 0.
 */
int shell_help(char **pars, char __attribute__((__unused__)) **front)
{
	if (!pars[0])
		help_all_func();
	else if (strcmp_func(pars[0], "alias") == 0)
		help_alias_func();
	else if (strcmp_func(pars[0], "cd") == 0)
		help_cd_func();
	else if (strcmp_func(pars[0], "exit") == 0)
		help_exit_func();
	else if (strcmp_func(pars[0], "env") == 0)
		help_env();
	else if (strcmp_func(pars[0], "setenv") == 0)
		help_set_env();
	else if (strcmp_func(pars[0], "unsetenv") == 0)
		help_unset_env();
	else if (strcmp_func(pars[0], "help") == 0)
		help_help_func();
	else
		write(STDERR_FILENO, name, strlen_func(name));

	return (0);
}
