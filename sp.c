#include "shell_.h"

int token_func(char *s, char *d);
int count_func(char *s, char *d);
char **strtok_func(char *x, char *d);

/**
 * token_func- Find location of the delimiter index mark.
 * @s: string to searche
 * @d: Delimiter Characte
 *
 * Return: Delimiter index marking 
 */
int token_func(char *s, char *d)
{
	int index_x= 0, e = 0;

	while (*(s + index_x) && *(s + index_x) != *d)
	{
		e++;
		index_x++;
	}

	return (e);
}

/**
 * count_func - Count the number of delimited word in string .
 * @s: string to searche
 * @d: Delimiter Character
 *
 * Return: Number of words contained.
 */
int count_func(char *s, char *d)
{
	int index_x, k = 0, e = 0;

	for (index_x = 0; *(s + index_x); index_x++)
		e++;

	for (index_x = 0; index_x < e; index_x++)
	{
		if (*(s + index_x) != *d)
		{
			k++;
			index_x += token_func(s + index_x, d);
		}
	}

	return (k);
}

/**
 * strtok_func - Tokenize String 
 * @x: string
 * @d: Delimiter character to tokenize the String by it .
 *
 * Return: pointer to an array with tokenized words.
 */
char **strtok_func(char *x, char *d)
{
	char **str;
	int index_x = 0, k, t, ch, i;

	k = count_func(x, d);
	if (k == 0)
		return (NULL);

	str = malloc(sizeof(char *) * (k + 2));
	if (!str)
		return (NULL);

	for (t = 0; t < k; t++)
	{
		while (x[index_x] == *d)
			index_x++;

		ch = token_func(x + index_x, d);

		str[t] = malloc(sizeof(char) * (ch + 1));
		if (!str[t])
		{
			for (index_x -= 1; index_x >= 0; index_x--)
				free(str[index_x]);
			free(str);
			return (NULL);
		}

		for (i = 0; i < ch; i++)
		{
			str[t][i] = x[index_x];
			index_x++;
		}

		str[t][i] = '\0';
	}
	str[t] = NULL;
	str[t + 1] = NULL;

	return (str);
}
