/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:50:13 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 12:00:13 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envl.h"

char	*join_key_value_to_string(t_environ *env)
{
	char	*to_return;

	if (env->key && env->value)
	{
		to_return = ft_join_and_free(ft_strdup(env->key), ft_strdup("="));
		to_return = ft_join_and_free(to_return, ft_strdup(env->value));
	}
	else
		to_return = ft_strdup(env->key);
	return (to_return);
}

char	**envl_to_envp(t_list *envl)
{
	int			size;
	t_list		*tmp;
	t_environ	*tmp_env;
	char		**to_return;
	int			idx;

	tmp = envl->next;
	size = ft_lstsize(tmp);
	to_return = malloc(sizeof(char *) * (size + 1));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return[size] = NULL;
	idx = 0;
	while (idx < size)
	{
		tmp_env = tmp->content;
		to_return[idx] = join_key_value_to_string(tmp_env);
		idx++;
		tmp = tmp->next;
	}
	return (to_return);
}

char	*get_value_by_key(t_list *envl, char *key)
{
	t_environ	*target;

	target = find_env_by_key(envl, key);
	if (target == NULL)
		return (NULL);
	return (ft_strdup(target->value));
}

void	set_exit_code(t_list *envl, int exit_code)
{
	t_environ	*question;

	question = find_env_by_key(envl, "?");
	free(question->value);
	question->value = ft_itoa(exit_code);
}

t_environ	*get_environ(void)
{
	t_environ	*to_return;

	to_return = malloc(sizeof(t_environ));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	return (to_return);
}
