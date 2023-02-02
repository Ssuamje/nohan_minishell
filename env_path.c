/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:59 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/02 23:06:10 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	free_env_path(t_env *env)
{
	int	i;

	i = -1;
	while (env->path[++i] != NULL)
		free(env->path[i]);
	free(env->path);
}

void	env_path(t_env *env, char **envp)
{
	int		i;
	char	*tmp_path;
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
