#include "shell.h"

/**
 * _myenv - handles env command
 * @info: pointer to the struct
 * 
 * Return: 0 on success
 */
int _myenv(info_t *info)
{
    int j;
    for (j = 0; info->environ[j]; j++)
    {
        _puts(info->environ[j]);
        _puts("\n");
    }
    return (0);
}

/**
 * _getenv - find the value of the environ
 * @info: struct
 * @nm: the var name
 * 
 * Return: the value on success, NULL otherwise
 */
char *_getenv(info_t *info, const char *nm)
{
    list_t *nd = info->env;
    char *ptr;

    if (!info || !nm) {
        return NULL;
    }

    while (nd) {
        ptr = starts_with(nd->str, nm);
        if (ptr && *ptr) {
            return (ptr);
        }
        nd = nd->next;
    }
    return (NULL);
}

/**
 * _mysetenv - handles setenv command
 * @info: pointer to the struct
 * 
 * Return: 0 on success, 1 on failure
 */
int _mysetenv(info_t *info)
{
    if (info->argc < 3)
        return (1);
    if (_getenv(info, info->argv[1]))
        _unsetenv(info, info->argv[1]);
    if (!add_node_end(&(info->env), info->argv[1], _atoi(info->argv[2])))
        return (1);
    info->env_changed = 1;
    return (0);
}

/**
 * _myunsetenv - handles unsetenv command
 * @info: pointer to the struct
 * 
 * Return: 0 on success, 1 on failure
 */
int _myunsetenv(info_t *info)
{
    if (info->argc < 2)
        return (1);
    if (!_getenv(info, info->argv[1]))
        return (1);
    delete_node_at_index(&(info->env), get_node_index(info->env, node_starts_with(info->env, info->argv[1], '=')));
    info->env_changed = 1;
    return (0);
}

/**
 * populate_env_list - populates environment variables list
 * @info: pointer to the struct
 * 
 * Return: 0 on success, 1 on failure
 */
int populate_env_list(info_t *info)
{
    int j;
    char *s;

    for (j = 0; environ[j]; j++)
    {
        s = _strdup(environ[j]);
        if (!s)
            return (1);
        if (!add_node_end(&(info->env), s, 0))
        {
            free(s);
            return (1);
        }
        free(s);
    }
    return (0);
}

