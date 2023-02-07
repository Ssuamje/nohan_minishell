/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:59 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/07 22:08:59 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

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
	int		flag;

	flag = 1;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			tmp_path = ft_strdup(envp[i] + 5);
			flag--;
		}
	}
	if (flag)
	{
		info->path = NULL;
		return ;
	}
	info->path = ft_split(tmp_path, ':');
	free(tmp_path);
	i = -1;
	while (info->path[++i])
		info->path[i] = ft_join_and_free(info->path[i], ft_strdup("/"));
}
