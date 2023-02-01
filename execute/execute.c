/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/01 16:06:52 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	env_command(t_process *cur_proc, t_process *next_proc, int pfd[], char **path, char **envp)
{
	int		i;
	char	*full_path;
	pid_t	pid;
	int		status;

	status = -1;
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		if (next_proc != NULL)
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		redirect_in(cur_proc);
		redirect_out(cur_proc);
		i = -1;
		while (path[++i])
		{
			full_path = ft_strjoin(path[i], cur_proc->cmd[0]);
			free(path[i]);
			execve(full_path, cur_proc->cmd, envp);
		}
		exit(0);
	}
	if (pid > 0)
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
	}
	if (next_proc == NULL)
		waitpid(pid, &status, 0);
}

void	execute(t_process *cur_proc, t_process *next_proc, int pfd[], char **path, char **envp)
{
	env_command(cur_proc, next_proc, pfd, path, envp);
}