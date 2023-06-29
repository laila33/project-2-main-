#include "shell.h"

/**
 * history_fun - displays the history
 *
 * @info: structure
 *
 * Return: 0
*/

int history_fun(info_tt *info)
{
	print_node(info->the_history);
	return (0);
}

/**
 * unsetalias_fun - unset alias to string
 *
 * @info: struct
 * @s: string
 *
 * Return: 0 success 1 if fail
*/

int unsetalias_fun(info_tt *info, char *s)
{
	char *p, b;
	int r;

	p = strchr_func2(s, '=');
	if (!p)
		return (1);
	b = *p;
	*p = 0;
	r = delete_index(&(info->alias),
			find_node_index(info->alias, start_node(info->alias, s, -1)));
	*p = b;
	return (r);
}

/**
 * setalias_fun - set alias to string
 *
 * @v_name: struct
 * @lue: string
 *
 * Return: 0 success 1 if fail
*/

int setalias_fun(char *v_name, char *lue)
{
	alias_t *temp = aliases;
	int l, n, x;
	char *new_lue;

	*lue = '\0';
	lue++;
	l = strlen_func(lue) - _strspn(lue, "'\"");
	new_lue = malloc(sizeof(char) * (l + 1));
	if (!new_lue)
		return;
	for (n = 0, x = 0; lue[n]; n++)
	{
		if (lue[n] != '\'' && lue[n] != '"')
			new_lue[x++] = lue[n];
	}
	new_lue[x] = '\0';
	while (temp)
	{
		if (strcmp_func(v_name, temp->name) == 0)
		{
			free(temp->lue);
			temp->lue = new_lue;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, v_name, new_lue);
}

/**
 * printalias_fun - print alias string
 *
 * @alias: alias node
 *
 * Return: 0 success 1 if fail
*/

int printalias_fun(alias_t *alias)
{
	char *aliasstg;
	int l = strlen_func(alias->name) + strlen_func(alias->lue) + 4;

	aliassg = malloc(sizeof(char) * (l + 1));
	if (!aliassg)
		return;
	strcpy_func1(aliasstg, alias->name);
	strcat_func(aliassg, "='");
	strcat_func(aliassg, alias->lue);
	strcat_func(aliassg, "'\n");

	write(STDOUT_FILENO, aliassg, l);
	free(aliassg);
}

/**
 * alias_fun - man alias
 *
 * @ar: struct
 * @fr: struct
 *
 * Return: 0
*/

int alias_fun(char **ar, char **fr)
{
	alias_t *temp = aliases;
	int n, rt = 0;
	char *lue;

	if (!ar[0])
	{
		while (temp)
		{
			printalias_fun(temp);
			temp = temp->next;
		}
		return (rt);
	}
	for (n = 0; ar[n]; n++)
	{
		temp = aliases;
		lue = strchr_func2(ar[n], '=');
		if (!lue)
		{
			while (temp)
			{
				if (strcmp_func(ar[n], temp->name) == 0)
				{
					printalias_fun(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				rt = create_error(ar + n, 1);
		}
		else
			setalias_fun(ar[n], lue);
	}
	return (rt);
}
