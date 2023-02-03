/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:59 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/03 16:29:22 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	free_env_path(t_info *info)
{
	int	i;

	i = -1;
	while (info->path[++i] != NULL)
		free(info->path[i]);
	free(info->path);
}

void	env_path(t_info *info, char **envp)
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
	info->path = ft_split(tmp_path, ':');
	free(tmp_path);
	i = -1;
	while (info->path[++i])
	{
		tmp_free = info->path[i];
		info->path[i] = ft_strjoin(info->path[i], "/");
		free(tmp_free);
	}
}
