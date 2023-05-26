#include "shell.h"

/**
 * free_list_full - frees list_s and all contained pointers
 * @head: linked list , list_s
 */
void free_list_full(list_s *head)
{
	list_s *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		do_mem(0, hold->ptr);
		do_mem(0, hold);
	}
}

/**
 * get_node_at_index - return nth node of a linked list
 * @head: pointer to the start of linked list
 * @index: index
 * Return: the nth node
 */
list_s *get_node_at_index(list_s *head, unsigned int index)
{
	unsigned int i = 0;

	for (i = 0; head; i++, head = (*head).next)
		if (i == index)
			return (head);
	return (NULL);
}

/**
 * insert_node_at_index - inserts a new node at a given position
 * @head: pointer to the beginning of linked list
 * @idx: index where to insert
 * @ptr: value for ptr
 * Return: address of new node or NULL if fails
 */
list_s *insert_node_at_index(list_s **head, unsigned int idx, char *ptr)
{
	list_s *new = NULL, *hold = *head;
	unsigned int i = 0;

	if (!idx)
	{
		new = do_mem(sizeof(list_s), NULL);
		if (!new)
			return (NULL);

		(*new).ptr = ptr;
		(*new).next = *head;

		*head = new;

		return (*head);
	}

	while (hold)
	{
		if (i == (idx - 1))
		{
			new = do_mem(sizeof(list_s), NULL);
			if (!new)
				return (NULL);
			(*new).ptr = ptr;
			(*new).next = (*hold).next;
			(*hold).next = new;
			return (new);
		}
		hold = (*hold).next;
		i++;
	}
	return (NULL);
}

/**
 * delete_node_at_index - deletes a node at a given position
 * @head: pointer to the beginning of linked list
 * @index: index to be deleted
 * Return: 1 if succesful -1 if fails
 */
int delete_node_at_index(list_s **head, unsigned int index)
{
	list_s *hold = NULL, *delete = NULL;
	unsigned int i = 0, action = 0;

	if (!*head)
		return (-1);
	for (i = 0, hold = *head; hold && index; i++, hold = (*hold).next)
		if (i == (index - 1))
		{
			action = 1;
			break;
		}

	if (action)
	{
		delete = (*hold).next;
		(*hold).next = (*delete).next;
		do_mem(0, delete);
		return (1);
	}
	else if (!index && (**head).next)
	{
		delete = *head;
		*head = (*delete).next;
		do_mem(0, delete);
		return (1);
	}
	else if (!index && *head)
	{
		*head = NULL;
		do_mem(0, *head);
		return (1);
	}
	return (-1);
}
