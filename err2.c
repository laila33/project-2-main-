#include "shell_.h"

char *err_126(char **pars);
char *err_127(char **pars);

/**
 * err_126 - Creates an err message for permission denied failures.
 * @pars: An array of arguments passed to the command.
 *
 * Return: The err string.
 */
/**
 *  generates an error message with a specific format and returns it.
 * 
 * @param pars An array of strings (char pointers)
 * 
 * @return a pointer to a character array (string) that contains an error message.
 */
char *err_126(char **pars)
{
	char *err, *hist_str;
	int len;

	hist_str = itoa_func(x);
	if (!hist_str)
		return (NULL);

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
	strcat_func(err, ": ");
	strcat_func(err, pars[0]);
	strcat_func(err, ": Permission denied\n");

	free(hist_str);
	return (err);
}

/**
 * err_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
/**
 *  `err_127` generates an error message with the given arguments and returns it as a
 * string.
 * 
 * @param args args is a pointer to a pointer to a character. It is an array of strings, where each
 * string represents an argument.
 * 
 * @return a pointer to a character array (string) that contains an error message.
 */
char *err_127(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = itoa_func(x);
	if (!hist_str)
		return (NULL);

	len = strlen_func(name) + strlen_func(hist_str) + strlen_func(args[0]) + 16;
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
	strcat_func(err, args[0]);
	strcat_func(err, ": not found\n");

	free(hist_str);
	return (err);
}
