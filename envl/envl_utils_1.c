/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:51:50 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 12:00:39 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envl.h"

int	is_key_in_envl(t_list *envl, char *key)
{
	t_list		*tmp;
	t_environ	*tmp_env;

	tmp = envl;
	while (tmp != NULL)
	{
		tmp_env = tmp->content;
		if (tmp_env != NULL \
		&& ft_strcmp(tmp_env->key, key) == TRUE)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

t_environ	*find_env_by_key(t_list *envl, char *key)
{
	t_list		*tmp;
	t_environ	*tmp_env;

	tmp = envl->next;
	while (tmp != NULL)
	{
		tmp_env = tmp->content;
		if (ft_strcmp(tmp_env->key, key) == TRUE)
			return (tmp_env);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_only_key_to_list(t_list *envl, char *env)
{
	t_environ	*content;

	if (is_key_in_envl(envl, env) == FALSE)
	{
		content = get_environ();
		content->key = ft_strdup(env);
		content->value = NULL;
		ft_lstadd_back(&envl, ft_lstnew(content));
	}
}

void	delete_env_by_key(t_list *envl, char *key)
{
	t_list		*tmp;
	t_environ	*tmp_env;

	tmp = envl->next;
	while (tmp != NULL)
	{
		tmp_env = tmp->content;
		if (ft_strcmp(tmp_env->key, key) == TRUE)
		{
			free(tmp_env->key);
			free(tmp_env->value);
			ft_lstpop(envl, tmp, 0);
			return ;
		}
		tmp = tmp->next;
	}
}
