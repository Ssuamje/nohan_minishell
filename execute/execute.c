/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:55:10 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 22:25:50 by hyungnoh         ###   ########.fr       */
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
	printf("hello hi\n");
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		if (next_proc != NULL) // need to modify
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
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
	// ft_putstr("before\n");
	if (next_proc == NULL) // need to modify
	{
		// ft_putstr("touched\n");
		waitpid(pid, &status, 0);
	}
	// ft_putstr("after\n");
}

void	execute(t_process *cur_proc, t_process *next_proc, int pfd[], char **path, char **envp)
{
	redirect_in(cur_proc);
	redirect_out(cur_proc);
	env_command(cur_proc, next_proc, pfd, path, envp);
}
