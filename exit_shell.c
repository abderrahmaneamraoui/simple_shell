#include "shell.h"

/**
 * do_mem - malloc, free, or free all with a static record
 * @size: the size to malloc if non-0
 * @ptr: the pointer to free if non-NULL
 * Return: the malloc'd pointer if malloc, otherwise the result of free
 */
void *do_mem(size_t size, void *ptr)
{
	static list_t *all;
	void *ret = NULL;
	int i = 0, len = 0;

	if (size)
	{
		ret = malloc(size);
		if (!ret)
			exit_shell(2, "malloc failed", EXIT_FAILURE);
		for (i = 0; (unsigned int)i < size; i++)
			((char *)ret)[i] = 0;
		__add_node_end(&all, ret);
		return (ret);
	}
	else if (ptr)
	{
		len = __list_len(all);
		for (i = 0; i < len; i++)
		{
			if (__get_node_at_index(all, i)->ptr == ptr)
			{
				__delete_node_at_index(&all, i);
				break;
			}
		}
		free(ptr);
		return (NULL);
	}
	else
	{
		__free_list_full(all);
		return (NULL);
	}
	return (NULL);
}

/**
 * exit_shell - custom exit with error message
 * @fd: file descriptor
 * @msg: message
 * @code: numerical exit code
 */

void exit_shell(int fd, char *msg, int code)
{
	if (*msg)
	{
		write(fd, msg, _strlen(msg));
	}

	do_mem(0, NULL);

	exit(code);
}
