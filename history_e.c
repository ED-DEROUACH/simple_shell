#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: struct
 * Return: allocated string
 */

char *get_history_file(info_t *info)
{
	char *tuf, *tir;

	tir = _getenv(info, "HOME=");
	if (!tir)
		return (NULL);
	tuf = malloc(sizeof(char) * (_strlen(tir) + _strlen(HIST_FILE) + 2));
	if (!tuf)
		return (NULL);
	tuf[0] = 0;
	_strcpy(tuf, tir);
	_strcat(tuf, "/");
	_strcat(tuf, HIST_FILE);
	return (tuf);
}

/**
 * write_history - creates a file
 * @info: struct
 *
 * Return: 1 on success, otherwise -1
 */
int write_history(info_t *info)
{
	ssize_t file_d;
	char *file_n = get_history_file(info);
	list_t *nd = NULL;

	if (!file_n)
		return (-1);

	file_d = open(file_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_n);
	if (file_d == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, file_d);
		_putfd('\n', file_d);
	}
	_putfd(BUF_FLUSH, file_d);
	close(file_d);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int j, l = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat stt;
	char *buf = NULL, *file_n = get_history_file(info);

	if (!file_n)
		return (0);

	fd = open(file_n, O_RDONLY);
	free(file_n);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &stt))
		fsize = stt.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + l, linecount++);
			l = j + 1;
		}
	if (l != j)
		build_history_list(info, buf + l, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @line_c: history linecount
 * Return: 0
 */
int build_history_list(info_t *info, char *buff, int line_c)
{
	list_t *nd = NULL;

	if (info->history)
		nd = info->history;

	add_node_end(&nd, buff, line_c);

	if (!info->history)
		info->history = nd;

	return (0);
}

/**
 * renumber_history - give a numb to an old linked list
 * @info: Struct
 * Return: the new numb
 */
int renumber_history(info_t *info)
{
	list_t *nd = info->history;
	int x;

	while (nd)
	{
		nd->num = x++;
		nd = nd->next;
	}
	return (info->histcount = x);
}
