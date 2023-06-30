#include "shell_.h"

int cant_func(char *fpath);
int proc_func(char *fpath, int *exe_e);

/**
 * cant_func-File doesn't exist or lacks proper permissions, priNT cant open e_e.
 * @f_path: Path to   f.
 * Return: (127)
 */

int cant_func(char *f_path)
{
	char *e_e, *h_str;
	int e;

	h_str = itoa_func(x);
	if (!h_str)
		return (127);

	e = strlen_func(name) + strlen_func(h_str) + strlen_func(f_path) + 16;
	e_e = malloc(sizeof(char) * (e + 1));
	if (!e_e)
	{
		free(h_str);
		return (127);
	}

	strcpy_func(e_e, name);
	strcpy_func(e_e, ": ");
	strcpy_func(e_e, h_str);
	strcpy_func(e_e, ": Can't open ");
	strcpy_func(e_e, f_path);
	strcpy_func(e_e, "\n");

	free(h_str);
	write(STDERR_FILENO, e_e, e);
	free(e_e);
	return (127);
}

/**
 * proc_func - take f and Attempt to run the command.
 * @f_path: Path to  f.
 * @exe_e: Return value of the last executed command.
 *
 * Return: If f couldn't be opened - 127 or -1or
 *  return value of the  command run.
 */
int proc_func(char *f_path, int *exe_e)
{
	ssize_t f, read_d, j;
	unsigned int sizee = 0;
	unsigned int oldd = 120;
	char *l_count, **arg_s, **front_f;
	char buffer[120];
	int result;

	x = 0;
	f = open(f_path, O_RDONLY);
	if (f == -1)
	{
		*exe_e = cant_func(f_path);
		return (*exe_e);
	}
	l_count = malloc(sizeof(char) * oldd);
	if (!l_count)
		return (-1);
	do {
		read_d = read(f, buffer, 119);
		if (read_d == 0 && sizee == 0)
			return (*exe_e);
		buffer[read_d] = '\0';
		sizee += read_d;
		l_count = re_alloc(l_count, oldd, sizee);
		strcpy_func(l_count, buffer);
		oldd = sizee;
	} while (read_d);
	for (j = 0; l_count[j] == '\n'; j++)
		l_count[j] = ' ';
	for (; j < sizee; j++)
	{
		if (l_count[j] == '\n')
		{
			l_count[j] = ';';
			for (j += 1; j < sizee && l_count[j] == '\n'; j++)
				l_count[j] = ' ';
		}
	}
	variable_repl_func(&l_count, exe_e);
	handle_line_func(&l_count, sizee);
	arg_s = strtok_func(l_count, " ");
	free(l_count);
	if (!arg_s)
		return (0);
	if (check_parms(arg_s) != 0)
	{
		*exe_e = 2;
		collect_parms(arg_s, arg_s);
		return (*exe_e);
	}
	front_f = arg_s;

	for (j = 0; arg_s[j]; j++)
	{
		if (strncmp_func(arg_s[j], ";", 1) == 0)
		{
			free(arg_s[j]);
			arg_s[j] = NULL;
			result = call_parms(arg_s, front_f, exe_e);
			arg_s = &arg_s[++j];
			j = 0;
		}
	}

	result = call_parms(arg_s, front_f, exe_e);

	free(front_f);
	return (result);
}
