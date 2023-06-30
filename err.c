#include "shell_.h"

int num_length(int num);
char *itoa_func(int num);
int generate_error(char **args, int err);

/**
 * num_length - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
/**
 *  "num_length" calculates the length of a given number, including the negative sign if
 * applicable.
 * 
 * @param num_ The parameter `num_` is an integer that represents the number for which we want to
 * determine the length.
 * 
 * @return the length of the given number.
 */
int num_length(int num)
{
	unsigned int numm;
	int len = 1;

	if (num < 0)
	{
		len++;
		numm = num * -1;
	}
	else
	{
		numm= num;
	}
	while (numm > 9)
	{
		len++;
		numm /= 10;
	}

	return (len);
}

/**
 * itoa_func - Converts an integer to a string.
 * @num_: The integer.
 *
 * Return: The converted string.
 */
/**
 *  `itoa_func` converts an integer to a string representation.
 * 
 * @param num_ The parameter `num_` is an integer that represents the number to be converted to a
 * string.
 * 
 * @return a pointer to a character array (string) that represents the input number as a string.
 */
char *itoa_func(int num)
{
	char *buffer;
	int len = num_length(num);
	unsigned int numm;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		numm = num * -1;
		buffer[0] = '-';
	}
	else
	{
		numm = num;
	}

	len--;
	do {
		buffer[len] = (numm % 10) + '0';
		num /= 10;
		len--;
	} while (num > 0);

	return (buffer);
}


/**
 * generate_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
/**
 *  "generate_error" takes in arguments and an error code, and based on the error code, it
 * generates an error message and writes it to the standard error output.
 * 
 * @param args args is a pointer to a pointer to a character. It is an array of strings, where each
 * string represents a command-line argument passed to the program.
 * @param err The parameter "err" is an integer that represents the error code. It is used in a switch
 * statement to determine which error function to call. The error functions are named err_env_func,
 * err_1, err_2_exit, err_2_syntax, err_2_cd, err_126
 * 
 * @return the value of the variable `err`.
 */
int generate_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = err_env_func(args);
		break;
	case 1:
		error = err_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = err_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = err_2_syntax(args);
		else
			error = err_2_cd(args);
		break;
	case 126:
		error = err_126(args);
		break;
	case 127:
		error = err_127(args);
		break;
	}
	write(STDERR_FILENO, error, strlen_func(error));

	if (error)
		free(error);
	return (err);

}
