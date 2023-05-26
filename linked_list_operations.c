#include "shell.h"

/**
 * __list_len - size of a list_t
 * @h: struct list_t, first node
 * Return: number of nodes
 */
size_t __list_len(list_t *h)
{
	int i = 0;

	for (i = 0; h; i++, h = h->next)
		;
	return (i);
}


/**
 * __add_node - adds a new node at the beginning of a list_t list
 * @head: struct list_t, first node
 * @ptr: the pointer data
 * Return: new list_t
 */
list_t *__add_node(list_t **head, void *ptr)
{
	list_t *new = NULL;

	new = malloc(sizeof(list_t));
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
 * __add_node_end - adds a new node at the end of a list_t list
 * @head: struct list_t, node
 * @ptr: the pointer data
 * Return: new list_t
 */
list_t *__add_node_end(list_t **head, void *ptr)
{
	list_t *new = NULL, *last = NULL;

	new = malloc(sizeof(list_t));
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
 * __free_list - frees list_t
 * @head: linked list , list_t
 */
void __free_list(list_t *head)
{
	list_t *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		free(hold);
	}
}
