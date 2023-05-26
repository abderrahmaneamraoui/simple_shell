#include "shell.h"

/**
 * arrayify - copy a char * linked list into a char **
 * @head: the head of the linked list
 * Return: a malloc'd char **
 */
char **arrayify(list_s *head)
{
	char **ret = NULL;
	char *tmp = NULL;
	char *tmp2 = NULL;
	int len = 0, i = 0;

	len = list_len(head);
	ret = do_mem(sizeof(char *) * (len + 1), NULL);
	for (i = 0; i < len; i++)
	{
		tmp2 = get_node_at_index(head, i)->ptr;
		tmp = do_mem(sizeof(char) * (_strlen(tmp2) + 1), NULL);
		tmp = _strcat(tmp, tmp2);
		ret[i] = tmp;
	}
	ret[i] = NULL;
	return (ret);
}

/**
 * listify - copy a char ** array into a malloc'd char * linked list
 * @arr: the char **
 * Return: a malloc'd char * linked list
 */
list_s *listify(char **arr)
{
	list_s *ret = NULL;
	char *tmp = NULL;
	int i = 0;

	while (arr[i])
	{
		tmp = do_mem(sizeof(char) * (_strlen(arr[i]) + 1), NULL);
		tmp = _strcat(tmp, arr[i]);
		add_node_end(&ret, tmp);
		i++;
	}
	return (ret);
}


/**
 * free_double_array - free a double char pointer
 * @list: the double char pointer
 */
void free_double_array(char **list)
{
	int i = 0;

	for (i = 0; list[i]; i++)
		do_mem(0, list[i]);
	do_mem(0, list);
}
