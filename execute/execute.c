/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/05 00:43:00 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	manage_pipe(t_process *cur, t_process *next, pid_t pid)
{
	if (pid == CHILD)
	{
		close(cur->pfd[0]);
		if (next != NULL)
			dup2(cur->pfd[1], STDOUT_FILENO);
		close(cur->pfd[1]);
	}
	else if (pid > 0)
	{
		close(cur->pfd[1]);
		dup2(cur->pfd[0], STDIN_FILENO);
		close(cur->pfd[0]);
	}
}

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
			return (tmp_path);
		free(tmp_path);
	}
	return (NULL);
}

void	execute_path(t_process *cur, char **path, char **envp)
{
	char	*full_path;

	full_path = find_full_path(cur, path);
	execve(full_path, cur->cmd, envp);
	exit(0);
}

int	execute_builtin(t_process *cur, t_info *info, pid_t pid)
{
	if (pid == CHILD)
	{
		if (ft_strcmp(cur->cmd[0], "echo"))
			builtin_echo(cur);
		else if (ft_strcmp(cur->cmd[0], "pwd"))
			builtin_pwd();
		else if (ft_strcmp(cur->cmd[0], "export") && cur->cmd[1] == NULL)
			builtin_export(cur->cmd, g_envl);
	}
	else if (pid == PARENTS)
	{
		if (info->process_cnt == 1)
		{
			if (ft_strcmp(cur->cmd[0], "cd"))
			{
				builtin_cd(cur);
				return (1);
			}
			else if (ft_strcmp(cur->cmd[0], "export") && cur->cmd[1] != NULL)
			{
				builtin_export(cur->cmd, g_envl);
				return (1);
			}
			else if (ft_strcmp(cur->cmd[0], "unset") && cur->cmd[1] != NULL)
			{
				builtin_unset(cur->cmd, g_envl);
				return (1);
			}
		}
	}
	return (0);
}

void	execute_program(t_process *cur, t_process *next, t_info *info, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == CHILD)
	{
		manage_pipe(cur, next, pid);
		redirection(cur);
		if (execute_builtin(cur, info, CHILD))
			;
		else
			execute_path(cur, info->path, envp);
	}
	if (pid > 0)
		manage_pipe(cur, next, pid);
	if (next == NULL)
	{
		waitpid(pid, &status, 0);
		set_exit_code(g_envl, status >> 8);
	}
}

void	execute(t_process *cur, t_process *next, t_info *info, char **envp)
{
	if (execute_builtin(cur, info, PARENTS))
		;
	else
		execute_program(cur, next, info, envp);
}
