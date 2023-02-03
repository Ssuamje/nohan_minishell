/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/03 17:45:38 by hyungnoh         ###   ########.fr       */
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
// is_builtin(cur) == BUILTIN_ECHO
// enum BUILTIN_ECHO, BUILTIN_EXPORT
// if (strcmp(cur->cmd, "echo") == TRUE)
//		return (BUILTIN_ECHO);

// int flag;
// is_fork_needed(BUILTIN_ECHO)

// (char **cmd, t_list *envl) 

int	execute_builtin(t_process *cur, t_info *info, pid_t pid)
{
	if (pid == CHILD)
	{
		if (ft_strcmp(cur->cmd[0], "echo"))
			builtin_echo(cur);
		else if (ft_strcmp(cur->cmd[0], "pwd"))
			builtin_pwd();
	}
	else
	{
		if (ft_strcmp(cur->cmd[0], "cd") && info->pipe_cnt == 0)
		{
			builtin_cd(cur);
			return (1);
		}
	}
	return (0);
}

// char **envp
// envp = envl_to_envp(g_envl);
// free_split(envp);

void	fork_child(t_process *cur, t_process *next, t_info *info, char **envp)
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
		waitpid(pid, &status, 0);
}

void	execute(t_process *cur, t_process *next, t_info *info, char **envp)
{
	if (execute_builtin(cur, info, PARENTS))
		;
	else
		fork_child(cur, next, info, envp);
}