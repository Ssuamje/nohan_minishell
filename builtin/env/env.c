/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:24:16 by sanan             #+#    #+#             */
/*   Updated: 2023/02/04 20:31:39 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	builtin_env(__attribute__((unused))char **cmd, t_list *envl)
{
	t_list		*tmp;
	t_environ	*tmp_env;
	
	tmp = envl->next;
	while (tmp != NULL)
	{
		tmp_env = tmp->content;
		if (ft_strcmp(tmp_env->key, "?") == FALSE)
		{
			if (tmp_env->value != NULL)
				printf("%s=\"%s\"\n", tmp_env->key, tmp_env->value);
			else
				printf("%s\n", tmp_env->key);
		}
		tmp = tmp->next;
	}
}