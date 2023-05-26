#include "shell.h"

/**
 * do_env - Get the env, or add a var, or delete a var
 * @add: a variable to add
 * @delete: a variable to delete
 * Return: the current environment after any changes
 */
char **do_env(char *add, char *delete)
{
	static list_s *my_env;
	char *tmp = NULL;
	int len = 0, i = 0, j = 0;

	if (!my_env)
	{
		my_env = listify((char **)add);
		return (NULL);
	}
	if (add)
		add_node_end(&my_env, add);
	else if (delete)
	{
		len = list_len(my_env);
		for (i = 0; i < len; i++)
		{
			j = 0;
			tmp = get_node_at_index(my_env, i)->ptr;
			while (delete && tmp && delete[j] && tmp[j] != '=')
			{
				if (delete[j] != tmp[j])
					break;
				j++;
			}
			if (!(delete[j]) && tmp[j] == '=')
			{
				delete_node_at_index(&my_env, i);
				break;
			}
		}
	}
	return (arrayify(my_env));
}
