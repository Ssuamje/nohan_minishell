/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:55:10 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/20 14:00:27 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	env_command(t_proc *proc, t_fd *fd, char **path, char **envp)
{
	int		i;
	char	*full_path;

	i = -1;
	while (path[++i])
	{
		full_path = ft_strjoin(path[i], proc->command[0]);
		execve(full_path, proc->command, envp);
	}
}

void	command(t_proc *proc, t_fd *fd, char **path, char **envp)
{
	env_command(proc, fd, path, envp);
}
