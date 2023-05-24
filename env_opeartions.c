#include "shell.h"

/**
 * get_path - get the path
 * Return: pointer
 */

char **get_path()
{
	char *temp = NULL;
	char **ret = NULL;

	temp = get_env_val("PATH");
	ret = _strtok(temp, ":");
	do_mem(0, temp);
	return (ret);
}

/**
 * get_env_value - get env variable value
 * @name: name of variable to get value of
 * Return: pointer
 */

char *get_env_value(char *name)
{
	int i = 0, j = 0;
	char **env = NULL;
	char *res = NULL;

	env = get_env();
	while (env[i])
	{
		j = 0;
		while (env[i][j] && name[j])
		{
			if (env[i][j] != name[j])
				break;
			j++;
		}

		if (name[j] == '\0' && env[i][j] == '=')
		{
			if (!env[i][j + 1])
				return (NULL);
			res = do_mem((_strlen((env[i]) + j + 1) + 1), NULL);
			_strcpy(res, (env[i] + j + 1));
			free_double(env);
			return (res);
		}
		i++;
	}
	free_double(env);
	return (NULL);
}

/**
 * get_env - get current environment
 * Return: the environment
 */

char **get_env(void)
{
	return (do_env(NULL, NULL));
}

/**
 * do_env - get env
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
