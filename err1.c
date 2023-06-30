#include "shell_.h"

char *err_env_func(char **pars);
char *err_1(char **pars);
char *err_2_exit(char **pars);
char *err_2_cd(char **pars);
char *err_2_syntax(char **pars);
/**
 * err_env_func - Creates an error message for shell_env_func errors.
 * @pars: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
/**
 *  `err_env_func` generates an error message string related to adding or removing from the
 * environment.
 * 
 * @param pars An array of strings (char pointers)
 * 
 * @return a pointer to a character array (string) that represents an error message.
 */
char *err_env_func(char **pars)
{
	char *err, *hist_str;
	int len;

	hist_str = itoa_func(x);
	if (!hist_str)
		return (NULL);

	pars--;
	len = strlen_func(name) + strlen_func(hist_str) + strlen_func(pars[0]) + 45;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	strcpy_func(err, name);
	strcat_func(err, ": ");
	strcat_func(err, hist_str);
	strcat_func(err, ": ");
	strcat_func(err, pars[0]);
	strcat_func(err, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (err);
}

/**
 * err_1 - Creates an err message for shell_alias errors.
 * @pars: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
/**
 *  generates an error message for a missing alias.
 * 
 * @param pars The parameter "pars" is a pointer to a pointer to a character array. It is expected to
 * contain a list of strings, with the first string being the name of an alias.
 * 
 * @return a dynamically allocated string that contains an error message.
 */
char *err_1(char **pars)
{
	char *err;
	int len;

	len = strlen_func(name) + strlen_func(pars[0]) + 13;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
		return (NULL);

	strcpy_func(err, "alias: ");
	strcat_func(err, pars[0]);
	strcat_func(err, " not found\n");

	return (err);
}

/**
 * err_2_exit - Creates an error message for shell_exit errors.
 * @pars: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
/**
 *  `err_2_exit` generates an error message string for an illegal number argument passed to
 * the `exit` function.
 * 
 * @param pars An array of strings (char pointers)
 * 
 * @return a pointer to a character array (string) that contains an error message.
 */
char *err_2_exit(char **pars)
{
	char *err, *hist_str;
	int len;

	hist_str = itoa_func(x);
	if (!hist_str)
		return (NULL);

	len = strlen_func(name) + strlen_func(hist_str) + strlen_func(pars[0]) + 27;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	strcpy_func(err, name);
	strcat_func(err, ": ");
	strcat_func(err, hist_str);
	strcat_func(err, ": exit: Illegal number: ");
	strcat_func(err, pars[0]);
	strcat_func(err, "\n");

	free(hist_str);
	return (err);
}

/**
 * err_2_cd - Creates an error message for shell_cd errors.
 * @pars: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
/**
 *  `err_2_cd` generates an error message for the `cd` command in a shell program.
 * 
 * @param pars A double pointer to a character array (string array)
 * 
 * @return a pointer to a character array (string).
 */
char *err_2_cd(char **pars)
{
	char *err, *hist_str;
	int len;

	hist_str = itoa_func(x);
	if (!hist_str)
		return (NULL);

	if (pars[0][0] == '-')
		pars[0][2] = '\0';
	len = strlen_func(name) + strlen_func(hist_str) + strlen_func(pars[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	strcpy_func(err, name);
	strcat_func(err, ": ");
	strcat_func(err, hist_str);
	if (pars[0][0] == '-')
		strcat_func(err, ": cd: Illegal option ");
	else
		strcat_func(err, ": cd: can't cd to ");
	strcat_func(err, pars[0]);
	strcat_func(err, "\n");

	free(hist_str);
	return (err);
}

/**
 * err_2_syntax - Creates an error message for syntax errors.
 * @pars: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
/**
 *  `err_2_syntax` generates an error message for a syntax error, including the name of the
 * function, a history string, and the unexpected token.
 * 
 * @param pars An array of strings (char pointers)
 * 
 * @return a pointer to a character array (string) that represents an error message.
 */
char *err_2_syntax(char **pars)
{
	char *err, *hist_str;
	int len;

	hist_str = itoa_func(x);
	if (!hist_str)
		return (NULL);

	len = strlen_func(name) + strlen_func(hist_str) + strlen_func(pars[0]) + 33;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	strcpy_func(err, name);
	strcat_func(err, ": ");
	strcat_func(err, hist_str);
	strcat_func(err, ": Syntax error: \"");
	strcat_func(err, pars[0]);
	strcat_func(err, "\" unexpected\n");

	free(hist_str);
	return (err);
}
