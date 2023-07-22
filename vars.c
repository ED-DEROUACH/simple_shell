#include "shellaq.h"
#include <stdio.h>


/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;
int result = 0;
*p = j;

switch (buf[j])
{
case ('|'):
if (buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_OR;
result = 1;
}
break;

case ('&'):
if (buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_AND;
result = 1;
}
break;

case (';'):
buf[j] = 0;
info->cmd_buf_type = CMD_CHAIN;
result = 1;
break;
}

return (result);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
*p = j;

if ((info->cmd_buf_type == CMD_AND && info->status) || (
			info->cmd_buf_type == CMD_OR && !info->status))
{
buf[i] = 0;
j = len;
}

}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
int i = 0;
list_t *node;
char *p;

do {
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);

free(info->argv[0]);

p = strchr(node->str, '=');
if (!p)
return (0);

p = strdup(p + 1);
if (!p)
return (0);

info->argv[0] = p;

i++;
} while (i < 10);

return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
int i = 0;
list_t *node;
char buffer[10];

for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;

if (!_strcmp(info->argv[i], "$?"))
{
sprintf(buffer, "%d", info->status);
replace_string(&(info->argv[i]), _strdup(buffer));
continue;
}
if (!_strcmp(info->argv[i], "$$"))
{
sprintf(buffer, "%d", getpid());
replace_string(&(info->argv[i]), _strdup(buffer));
continue;
}
node = node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_string(&info->argv[i], _strdup(""));
}
return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
free(*old);
*old = strdup(new);
if (*old)
return (1);
return (0);
}
