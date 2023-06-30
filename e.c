#include "shell_.h"

int shell_env_func(char **pars, char __attribute__((__unused__)) **front);
int shell_set_env_func(char **pars, char __attribute__((__unused__)) **front);
int shell_unset_env_func(char **pars, char __attribute__((__unused__)) **front);

/**
 *  prints the environment variables to the standard output.
 * 
 * @param pars A pointer to an array of strings, where each string represents a command-line argument.
 * @param __unused__ The `__unused__` attribute is used to indicate that a function parameter is
 * intentionally left unused. It is a way to suppress compiler warnings about unused variables. In this
 * case, the `__unused__` attribute is applied to the `front` parameter, indicating that it is not used
 * in the
 * 
 * @return 0.
 */
int shell_env_func(char **pars, char __attribute__((__unused__)) **front)
{
	int i;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen_func(environ[i]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)pars;
	return (0);
}


/**
 *  `shell_set_env_func` sets or updates an environment variable with a given name and
 * value.
 * 
 * @param pars An array of strings, where pars[0] is the name of the environment variable and pars[1]
 * is the value to set for that variable.
 * @param __unused__ The `__unused__` attribute is used to indicate that a function parameter is
 * intentionally unused. It is typically used to suppress compiler warnings about unused variables. In
 * this case, the `__unused__` attribute is applied to the `front` parameter, indicating that it is not
 * used in 
 * 
 * @return an integer value.
 */
int shell_set_env_func(char **pars, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int i;

	if (!pars[0] || !pars[1])
		return (generate_error(pars, -1));

	new_value = malloc(strlen_func(pars[0]) + 1 + strlen_func(pars[1]) + 1);
	if (!new_value)
		return (generate_error(pars, -1));
	strcpy_func(new_value, pars[0]);
	strcat_func(new_value, "=");
	strcat_func(new_value, pars[1]);

	env_var = get_env(pars[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (generate_error(pars, -1));
	}

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	free(environ);
	environ = new_environ;
	environ[i] = new_value;
	environ[i + 1] = NULL;

	return (0);
}


/**
 *  `shell_unset_env_func` is used to remove an environment variable from the current
 * environment.
 * 
 * @param pars An array of strings representing the command and its arguments.
 * @param __unused__ The `__unused__` attribute is used to indicate that a function parameter is
 * intentionally unused. It is typically used to suppress compiler warnings about unused variables. In
 * the given code, the `__unused__` attribute is applied to the `front` parameter, indicating that it
 * is not used within the
 * 
 * @return an integer value.
 */
int shell_unset_env_func(char **pars, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int i, index2;

	if (!pars[0])
		return (generate_error(pars, -1));
	env_var = get_env(pars[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (generate_error(pars, -1));

	for (i = 0, index2 = 0; environ[i]; i++)
	{
		if (*env_var == environ[i])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[i];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
