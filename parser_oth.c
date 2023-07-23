#include "shell.h"

/**
 * is_cmd - see if a file is executable
 * @info: struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicate a character
 * @pathstr: path string
 * @start: first index
 * @end: index where to stop
 * Return: pointer
 */
char *dup_chars(char *pathstr, int start, int end)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - find the path
 * @info: struct
 * @pathstr: path string
 * @cmd: the cmd to look for
 * Return: the full path or NULL othewise
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "/"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr = i;
		}
		i++;
	}
	return (NULL);
}
