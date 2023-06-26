#include "shell_.h"

/**
 * find_history_file - find the history file.
 *
 * @info: parameter struct.
 *
 * Return: allocated string containg history file.
 */

char find_history_file(info_t *info)
{
	char *buffer, *x;

	x = getenv_func(info, "HOME=");
	if (!x)
		return (NULL);
	buffer = malloc(sizeof(char) * (strlen_func(x) + strlen_func(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	strcpy_func(buffer, x);
	strcat_func(buffer, "/");
	strcat_func(buffer, HIST_FILE);
	return (buffer);
}




/**
 * history_w - creates a file, or add to an existing file.
 * @info: the parameter struct.
 *
 * Return: 1 or -1.
 */


int history_w(info_t *info)
{
	ssize_t f_d;
	char *name = find_history_file(info);
	list_t *c_node = NULL;

	if (!name)
		return (-1);

	f_d = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (f_d == -1)
		return (-1);
	for (c_node = info->history; c_node; c_node = c_node->next)
	{
		putsfd_print(c_node->s, f_d);
		putfd_func('\n', f_d);
	}
	putfd_func(_FLUSH, f_d);
	close(f_d);
	return (1);
}

/**
 * history_r - read history from file.
 *
 * @info: the parameter struct.
 *
 * Return: histcount on success, or 0.
 */
int history_r(info_t *info)
{
	int j, end = 0, lcount = 0;
	ssize_t f_d, rlen, sizee = 0;
	struct stat st;
	char *buffer = NULL, *fname = find_history_file(info);

	if (!fname)
		return (0);

	f_d = open(fname, O_RDONLY);
	free(fname);
	if (f_d == -1)
		return (0);
	if (!fstat(f_d, &st))
		sizee = st.st_size;
	if (sizee < 2)
		return (0);
	buffer = malloc(sizeof(char) * (sizee + 1));
	if (!buffer)
		return (0);
	rlen = read(f_d, buffer, sizee);
	buffer[sizee] = 0;
	if (rlen <= 0)
		return (free(buffer), 0);
	close(f_d);
	for (j = 0; j < sizee; j++)
		if (buffer[j] == '\n')
		{
			buffer[j] = 0;
			history_l(info, buffer + end, lcount++);
			end = j + 1;
		}
	if (end != j)
		history_l(info, buffer + end, lcount++);
	free(buffer);
	info->historycount = lcount;
	while (info->historycount-- >= HIST_MAX)
		remove_node(&(info->history), 0);
	history_rm(info);
	return (info->historycount);
}



/**
 * history_rm - renumber the history list after change.
 *
 * @info: Structure containing potential arguments.
 *
 * Return:  histcount.
 */
int history_rm(info_t *info)
{
	my_list_t *c_node = info->history;
	int j = 0;

	while (c_node)
	{
		c_node->number = j++;
		c_node = c_node->next;
	}
	return (info->historycount = j);
}



/**
 * history_l - add entry to a history list.
 *
 * @info: Structure containing potential arguments.
 * @buf:the buffer.
 *
 * @lcount:history  number of line count .
 *
 * Return: 0.
 */
int history_l(info_t *info, char *buf, int lcount)
{
	my_list_t *c_node = NULL;

	if (info->history)
		c_node = info->history;
	add_end_node(&c_node, buf, lcount);

	if (!info->history)
		info->history = c_node;
	return (0);
}