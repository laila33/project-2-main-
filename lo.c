#include "shell_.h"

char *set_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_path_func - Locates a cmd in the PATH.
 * @cmd: The cmd to locate.
 *
 * Return: If an error occurs or the cmd cannot be located - NULL.
 *         Otherwise - the full pathname of the cmd.
 */
char *get_path_func(char *cmd)
{
	char **path, *tmp;
	list_t *direcs, *top;
	struct stat st;

	path = get_env("PATH");
	if (!path || !(*path))
		return (NULL);

	direcs = get_path_dir(*path + 5);
	top = direcs;

	while (direcs)
	{
		tmp = malloc(strlen_func(direcs->dir) + strlen_func(cmd) + 2);
		if (!tmp)
			return (NULL);

		strcpy_func(tmp, direcs->dir);
		strcat_func(tmp, "/");
		strcat_func(tmp, cmd);

		if (stat(tmp, &st) == 0)
		{
			collect_e_list(top);
			return (tmp);
		}

		direcs = direcs->next;
		free(tmp);
	}

	collect_e_list(top);

	return (NULL);
}

/**
 * set_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *set_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(get_env("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += strlen_func(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				strcat_func(path_copy, pwd);
				strcat_func(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				strcat_func(path_copy, ":");
				strcat_func(path_copy, pwd);
			}
			else
				strcat_func(path_copy, ":");
		}
		else
		{
			strncat_func(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *get_path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *top = NULL;

	path_copy = set_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = strtok_func(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (end_node(&top, dirs[index]) == NULL)
		{
			collect_e_list(top);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (top);
}
