/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:24:16 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 15:26:40 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	builtin_env(__attribute__((unused))char **cmd, t_list *envl)
{
	t_list		*tmp;
	t_environ	*tmp_env;

	if (cmd[1] == NULL)
	{
		tmp = envl->next;
		while (tmp != NULL)
		{
			tmp_env = tmp->content;
			if (ft_strcmp(tmp_env->key, "?") == FALSE \
			&& tmp_env->value != NULL)
				printf("%s=%s\n", tmp_env->key, tmp_env->value);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("AengMuShell: env: no args!!\n");
		exit(1);
	}
	exit(0);
}
