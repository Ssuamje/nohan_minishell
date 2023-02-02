/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/02 16:59:56 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include <sys/stat.h>

char	*find_full_path(t_process *cur_proc, char **path)
{
	char 		*tmp_path;
	struct stat	sb;
	int			i;

	i = 0;
	while (path[++i])
	{
		tmp_path = ft_strjoin(path[i], cur_proc->cmd[0]);
		if (stat(tmp_path, &sb) == 0)
			return (tmp_path);
		free(tmp_path);
	}
	return (NULL);
}

void	env_command(t_process *cur_proc, t_process *next_proc, int pfd[], char **path, char **envp)
{
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
		full_path = find_full_path(cur_proc, path);;
		execve(full_path, cur_proc->cmd, envp);
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