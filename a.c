#include "shell_.h"

int shell_alias(char **pars, char __attribute__((__unused__)) **front);
void set_alias_func(char *var_name, char *value);
void print_alias_func(alias_t *alias);


/**
 * shell_alias is used to manage aliases in a shell program, allowing users to view
 * existing aliases or create new ones.
 * 
 * @param pars An array of strings representing the command and its arguments.
 * @param __unused__ The `__unused__` attribute is used to indicate that a function parameter is
 * intentionally unused. It is typically used to suppress compiler warnings about unused variables. In
 * this case, the `__unused__` attribute is applied to the `front` parameter, indicating that it is not
 * used in 
 * 
 * @return an integer value.
 */
int shell_alias(char **pars, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!pars[0])
	{
		while (temp)
		{
			print_alias_func(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; pars[i]; i++)
	{
		temp = aliases;
		value = strchr_func(pars[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (strcmp_func(pars[i], temp->name) == 0)
				{
					print_alias_func(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = generate_error(pars + i, 1);
		}
		else
			set_alias_func(pars[i], value);
	}
	return (ret);
}


/**
 *  `set_alias_func` sets the value of a variable in a linked list of aliases.
 * 
 * @param var_name A pointer to a character array representing the name of the variable to set the
 * alias for.
 * @param value The `value` parameter is a string that represents the new value for the alias.
 * 
 * @return The function does not explicitly return a value.
 */
void set_alias_func(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = strlen_func(value) - strspn_func(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (strcmp_func(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		end_alias(&aliases, var_name, new_value);
}


/**
 *  "print_alias_func" prints the name and value of an alias in the format
 * "name='value'\n".
 * 
 * @param alias The parameter "alias" is a pointer to a structure of type "alias_t".
 * 
 * @return nothing (void).
 */
void print_alias_func(alias_t *alias)
{
	char *alias_string;
	int len = strlen_func(alias->name) + strlen_func(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	strcpy_func(alias_string, alias->name);
	strcat_func(alias_string, "='");
	strcat_func(alias_string, alias->value);
	strcat_func(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}


/**
 *  updates aliases in a given array of strings by replacing any alias names with their
 * corresponding values.
 * 
 * @param pars The parameter "pars" is a pointer to a pointer to a character array. It is used to store
 * a list of command line arguments.
 * 
 * @return the updated array of strings, `pars`.
 */
char **update_aliases(char **pars)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (strcmp_func(pars[0], "alias") == 0)
		return (pars);
	for (i = 0; pars[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (strcmp_func(pars[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (strlen_func(temp->value) + 1));
				if (!new_value)
				{
					collect_parms(pars, pars);
					return (NULL);
				}
				strcpy_func(new_value, temp->value);
				free(pars[i]);
				pars[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (pars);
}

