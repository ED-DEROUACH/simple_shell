#include "shell.h"

/**
* is_cmd - see if the file is executable
* @info: struct
* @path: the path
* Return: 1 on success, 0 otherwise
*/
int is_cmd(info_t *info, char *path)
{
    struct stat s;

    if (!path)
        return (0);

    if (stat(path, &s) == -1)
        return (0);

    if (s.st_mode & S_IFREG && (s.st_mode & S_IXUSR || s.st_mode & S_IXGRP || s.st_mode & S_IXOTH))
    {
        return (1);
    }

    return (0);
}


/**
* dup_chars - duplicate a range of characters from string
* @path: the path
* @beg: the beginning of the string
* @end: the end the string
* Return: pointer to the new string
*/
char *dup_chars(char *path, int beg, int end)
{
    static char buffer[1024];
    int t = 0;

    if (!path || beg < 0 || end > _strlen(path))
        return NULL;

    while (beg < end)
    {
        buffer[t++] = path[beg++];
    }
    buffer[t] = 0;
    return (buffer);
}


/**
* find_path - find path to the string with cmd
* @info: struct
* @paths: path of the string
* @cmd: cmd
* Return: the path on success, NULL otherwise
*/
char *find_path(info_t *info, char *paths, char *cmd)
{
    int j = 0, curr = 0;
    char *path;

    if (!paths || !cmd)
        return (NULL);

    if ((_strlen(cmd) > 2) && starts_with(cmd, "/"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }

    while (1)
    {
        if (paths[j] == '\0' || paths[j] == ':')
        {
            path = dup_chars(paths, curr, j);
            if (path[0] == '\0')
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }

            if (is_cmd(info, path))
                return (path);

            if (paths[j] == '\0')
                break;

            curr = j + 1;
        }
        j++;
    }
    return (NULL);
}

