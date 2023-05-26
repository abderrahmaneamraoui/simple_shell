#include "shell.h"

/**
 * list_len - size of a list_s
 * @h: struct list_s, first node
 * Return: number of nodes
 */
size_t list_len(list_s *h)
{
	int i = 0;

	for (i = 0; h; i++, h = h->next)
		;
	return (i);
}


/**
 * add_node - adds a new node at the beginning of a list_s list
 * @head: struct list_s, first node
 * @ptr: the pointer data
 * Return: new list_s
 */
list_s *add_node(list_s **head, char *ptr)
{
	list_s *new = NULL;

	new = do_mem(sizeof(list_s), NULL);
	if (!new)
	{
		return (NULL);
	}
	new->ptr = ptr;
	new->next = *head;

	*head = new;
	return (new);
}

/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: struct list_s, node
 * @ptr: the pointer data
 * Return: new list_s
 */
list_s *add_node_end(list_s **head, char *ptr)
{
	list_s *new = NULL, *last = NULL;

	new = do_mem(sizeof(list_s), NULL);
	if (!new)
	{
		return (NULL);
	}

	new->ptr = ptr;
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		return (new);
	}

	for (last = *head; last->next != NULL; last = last->next)
		;

	last->next = new;
	return (new);
}

/**
 * free_list - frees list_s
 * @head: linked list , list_s
 */
void free_list(list_s *head)
{
	list_s *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		do_mem(0, hold);
	}
}
