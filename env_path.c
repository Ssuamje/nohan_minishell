/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:59 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 20:27:45 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_path(t_env *env, char **envp)
{
	int		i;
	char 	*tmp_path;
	char	*tmp_free;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			tmp_path = ft_strdup(envp[i] + 5);
	}
	env->path = ft_split(tmp_path, ':');
	free(tmp_path);
	i = -1;
	while (env->path[++i])
	{
		tmp_free = env->path[i];
		env->path[i] = ft_strjoin(env->path[i], "/");
		free(tmp_free);
	}
}
