#include "shell.h"

/**
 * _myexit - handles exit command
 * @info: pointer to the struct
 * 
 * Return: 1 on failure, doesn't return on success
 */
int _myexit(info_t *info)
{
    int exit_status = 0;

    if (info->argc > 1)
        exit_status = _atoi(info->argv[1]);
    free_info(info, 1);
    exit(exit_status);
}

/**
 * _mycd - handles cd command
 * @info: pointer to the struct
 * 
 * Return: 0 on success, 1 on failure
 */
int _mycd(info_t *info)
{
    char *path, *ptr;
    int res;

    if (info->argc < 2)
        path = _getenv(info, "HOME");
    else if (_strcmp(info->argv[1], "-") == 0)
        path = _getenv(info, "OLDPWD");
    else
        path = info->argv[1];

    if (path == NULL)
        return (1);

    res = chdir(path);
    if (res == -1) {
        perror("Error: ");
        return (1);
    }

    ptr = getcwd(info->oldpwd, PATH_MAX);
    if (!ptr) {
        perror("Error: ");
        return (1);
    }

    _setenv(info, "OLDPWD", info->pwd);
    _setenv(info, "PWD", info->oldpwd);
    _strcpy(info->pwd, info->oldpwd);
    return (0);
}

/**
 * _myhelp - handles help command
 * @info: pointer to the struct
 * 
 * Return: 0 on success, 1 on failure
 */
int _myhelp(info_t *info)
{
    (void)info;
    return (0);
}

