/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/02 23:35:02 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include <sys/stat.h>

char	*find_full_path(t_process *cur, char **path)
{
	char		*tmp_path;
	struct stat	sb;
	int			i;

	i = 0;
	while (path[++i])
	{
		tmp_path = ft_strjoin(path[i], cur->cmd[0]);
		if (stat(tmp_path, &sb) == 0)
		{
			printf("full path : %s\n", tmp_path);
			return (tmp_path);
		}
		free(tmp_path);
	}
	return (NULL);
}

void	env_command(t_process *cur, t_process *next, char **path, char **envp)
{
	char	*full_path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(cur->pfd[0]);
		if (next != NULL)
			dup2(cur->pfd[1], STDOUT_FILENO);
		close(cur->pfd[1]);
		redirect_in(cur);
		redirect_out(cur);
		full_path = find_full_path(cur, path);
		execve(full_path, cur->cmd, envp);
		exit(0);
	}
	if (pid > 0)
	{
		close(cur->pfd[1]);
		dup2(cur->pfd[0], STDIN_FILENO);
		close(cur->pfd[0]);
	}
	if (next == NULL)
		waitpid(pid, &status, 0);
}

void	execute(t_process *cur, t_process *next, char **path, char **envp)
{
	env_command(cur, next, path, envp);
}
