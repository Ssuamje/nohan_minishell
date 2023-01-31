/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:55:10 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 20:23:25 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	env_command(t_proc *proc, int pfd[], char **path, char **envp)
{
	int		i;
	char	*full_path;
	pid_t	pid;
	int		status;

	(void)status;
	status = -1;
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		if (proc->next != NULL)
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		i = -1;
		while (path[++i])
		{
			full_path = ft_strjoin(path[i], proc->command[0]);
			execve(full_path, proc->command, envp);
		}
	}
	if (pid > 0)
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
	}
	if (proc->next == NULL)
		waitpid(pid, NULL, 0);
}

void	execute(t_proc *proc, int pfd[], char **path, char **envp)
{
	redirect_in(proc);
	redirect_out(proc);
	env_command(proc, pfd, path, envp);
}
