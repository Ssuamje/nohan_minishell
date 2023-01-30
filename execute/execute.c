/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:55:10 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/30 21:38:14 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	set_pipe(t_proc *proc)
{
	if (proc->prev != NULL) // 맨 앞일 때 제외
	{
		dup2(proc->pip[0], STDIN_FILENO);
		close(proc->pip[0]);
	}
	if (proc->next != NULL) // 맨 뒤일 때 제외
	{
		close(proc->next->pip[0]);
		dup2(proc->next->pip[1], STDOUT_FILENO);
	}
}

void	env_command(t_proc *proc, char **path, char **envp)
{
	int		i;
	char	*full_path;
	pid_t	pid;
	int		status;

	if (proc->next != NULL)
		pipe(proc->next->pip);
	pid = fork();
	if (pid == 0)
	{
		set_pipe(proc);
		i = -1;
		while (path[++i])
		{
			full_path = ft_strjoin(path[i], proc->command[0]);
			execve(full_path, proc->command, envp);
		}
	}
}

void	execute(t_proc *proc, char **path, char **envp)
{
	redirect_in(proc);
	redirect_out(proc);
	env_command(proc, path, envp);
}
