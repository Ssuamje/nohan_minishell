#include "../include/utils.h"

void	print_envl(t_list *envl)
{
	t_list		*tmp;
	t_environ 	*tmp_env;

	tmp = envl->next;
	while (tmp != NULL)
	{
		tmp_env = tmp->content;
		printf("{ key   : '%s'\n  value : '%s' }\n", tmp_env->key, tmp_env->value);
		printf("\n");
		tmp = tmp->next;
	}
}