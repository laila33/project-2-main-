#include "shell_.h"

char *get_parms(char *line, int *exe_ret);
int call_parms(char **parms, char **front, int *exe_ret);
int run_parms(char **parms, char **front, int *exe_ret);
int handle_parms(int *exe_ret);
int check_parms(char **parms);

/**
 * get_parms - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_parms(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t rd;
	char *prompt = "$ ";

	if (line)
		free(line);

	rd = get_line_func(&line, &n, STDIN_FILENO);
	if (rd == -1)
		return (NULL);
	if (rd == 1)
	{
		x++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_parms(line, exe_ret));
	}

	line[rd - 1] = '\0';
	variable_repl_func(&line, exe_ret);
	handle_line_func(&line, rd);

	return (line);
}

/**
 * call_parms - Partitions operators from commands and calls them.
 * @parms: An array of arguments.
 * @front: A double pointer to the beginning of parms.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_parms(char **parms, char **front, int *exe_ret)
{
	int ret, index;

	if (!parms[0])
		return (*exe_ret);
	for (index = 0; parms[index]; index++)
	{
		if (strncmp_func(parms[index], "||", 2) == 0)
		{
			free(parms[index]);
			parms[index] = NULL;
			parms = update_aliases(parms);
			ret = run_parms(parms, front, exe_ret);
			if (*exe_ret != 0)
			{
				parms = &parms[++index];
				index = 0;
			}
			else
			{
				for (index++; parms[index]; index++)
					free(parms[index]);
				return (ret);
			}
		}
		else if (strncmp_func(parms[index], "&&", 2) == 0)
		{
			free(parms[index]);
			parms[index] = NULL;
			parms = update_aliases(parms);
			ret = run_parms(parms, front, exe_ret);
			if (*exe_ret == 0)
			{
				parms = &parms[++index];
				index = 0;
			}
			else
			{
				for (index++; parms[index]; index++)
					free(parms[index]);
				return (ret);
			}
		}
	}
	parms = update_aliases(parms);
	ret = run_parms(parms, front, exe_ret);
	return (ret);
}

/**
 * run_parms - Calls the execution of a command.
 * @parms: An array of arguments.
 * @front: A double pointer to the beginning of parms.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_parms(char **parms, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **parms, char **front);

	builtin = get_built_in_func(parms[0]);

	if (builtin)
	{
		ret = builtin(parms + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(parms, front);
		ret = *exe_ret;
	}

	x++;

	for (i = 0; parms[i]; i++)
		free(parms[i]);

	return (ret);
}

/**
 * handle_parms - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is rd - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_parms(int *exe_ret)
{
	int ret = 0, index;
	char **parms, *line = NULL, **front;

	line = get_parms(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	parms = strtok_func(line, " ");
	free(line);
	if (!parms)
		return (ret);
	if (check_parms(parms) != 0)
	{
		*exe_ret = 2;
		collect_parms(parms, parms);
		return (*exe_ret);
	}
	front = parms;

	for (index = 0; parms[index]; index++)
	{
		if (strncmp_func(parms[index], ";", 1) == 0)
		{
			free(parms[index]);
			parms[index] = NULL;
			ret = call_parms(parms, front, exe_ret);
			parms = &parms[++index];
			index = 0;
		}
	}
	if (parms)
		ret = call_parms(parms, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_parms - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @parms: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_parms(char **parms)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; parms[i]; i++)
	{
		cur = parms[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (generate_error(&parms[i], 2));
			nex = parms[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (generate_error(&parms[i + 1], 2));
		}
	}
	return (0);
}
