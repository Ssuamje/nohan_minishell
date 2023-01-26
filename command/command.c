/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:55:10 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/26 22:38:30 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	env_command(t_proc *proc, t_fd *fd, char **path, char **envp)
{
	int		i;
	char	*full_path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		i = -1;
		while (path[++i])
		{
			full_path = ft_strjoin(path[i], proc->command[0]);
			execve(full_path, proc->command, envp);
			free(full_path);
		}
		printf("minishell: %s: command not found\n", proc->command[0]);
	}
	wait(&status);
}

void	command(t_proc *proc, t_fd *fd, char **path, char **envp)
{
	if (proc->command[0] != NULL)
		env_command(proc, fd, path, envp);
}
