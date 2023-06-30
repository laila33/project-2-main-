#include "shell_.h"

char **cp_env_func(void);
void collect_env(void);
char **get_env(const char *var);

/**
 * cp_env_func - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
/**
 *  `cp_env_func` creates a copy of the environment variables and returns it as a double
 * pointer to strings.
 * 
 * @return  `cp_env_func` returns a pointer to a dynamically allocated array of strings,
 * which represents a copy of the environment variables.
 */
char **cp_env_func(void)
{
	char **new_env;
	size_t size;
	int i;

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_env[i] = malloc(strlen_func(environ[i]) + 1);

		if (!new_env[i])
		{
			for (i--; i >= 0; i--)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		strcpy_func(new_env[i], environ[i]);
	}
	new_env[i] = NULL;

	return (new_env);
}

/**
 * collect_env - Frees the the environment copy.
 */
/**
 *  "collect_env" frees the memory allocated for the environment variables.
 */
void collect_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
/**
 *  "get_env" searches for a specific environment variable and returns a pointer to its
 * value.
 * 
 * @param var The parameter "var" is a pointer to a character array, which represents the name of the
 * environment variable we are searching for.
 * 
 * @return a pointer to a pointer to a character array (char **).
 */
char **get_env(const char *var)
{
	int i, len;

	len = strlen_func(var);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp_func(var, environ[i], len) == 0)
			return (&environ[i]);
	}

	return (NULL);
}
