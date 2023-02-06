/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 13:32:06 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

#define RELATVIE 0
#define	ABSOLUTE 1

char	*find_full_path(t_process *cur, char **path, int *flag)
{
	char		*tmp_path;
	struct stat	sb;
	int			i;

	i = 0;
	if (stat(cur->cmd[0], &sb) == 0)
	{
		tmp_path = ft_strdup(cur->cmd[0]);
		*flag = ABSOLUTE;
		return (tmp_path);
	}
	while (path[++i])
	{
		tmp_path = ft_strjoin(path[i], cur->cmd[0]);
		if (stat(tmp_path, &sb) == 0)
			return (tmp_path);
		free(tmp_path);
	}
	return (NULL);
}

int	check_cmd(t_process *cur, char **path)
{
	char		*tmp_path;
	struct stat	sb;
	int			i;

	i = 0;
	if (cur->cmd[0][0] == '/') // 절대경로인 것 처럼 인식되는 경우
		return (TRUE);
	while (path[++i])
	{
		tmp_path = ft_strjoin(path[i], cur->cmd[0]);
		if (stat(tmp_path, &sb) == 0)
		{
			free(tmp_path);
			return (1);
		}
		free(tmp_path);
	}
	if (ft_strcmp(cur->cmd[0], "echo"))
		return (1);
	if (ft_strcmp(cur->cmd[0], "pwd"))
		return (1);
	if (ft_strcmp(cur->cmd[0], "export") && cur->cmd[1] == NULL)
		return (1);
	return (0);
}

void	manage_pipe(t_process *cur, t_process *next, char **path, pid_t pid)
{
	if (pid == CHILD)
	{
		close(cur->pfd[0]);
		if (next != NULL && check_cmd(cur, path))
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

int	find_last_slash_index(char *cmd)
{
	int	idx;

	idx = 0;
	while (cmd[idx])
		idx++;
	idx--;
	while (idx >= 0)
	{
		if (cmd[idx] == '/')
			return (idx);
		idx--;
	}
	return (-1);
}

void	parse_cmd(t_process *cur)
{
	char	*tmp;
	int		idx_slash;

	idx_slash = find_last_slash_index(cur->cmd[0]);
	if (idx_slash == -1)
		return ;
	tmp = ft_strdup(&(cur->cmd[0][idx_slash + 1]));
	free(cur->cmd[0]);
	cur->cmd[0] = tmp;
}

void	execute_path(t_process *cur, char **path, char **envp)
{
	char	*full_path;
	int		flag;

	flag = RELATVIE;
	full_path = find_full_path(cur, path, &flag);
	if (flag == ABSOLUTE)
		parse_cmd(cur);
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
			else if (ft_strcmp(cur->cmd[0], "env"))
			{
				builtin_env(cur->cmd, g_envl);
				return (1);
			}
			else if (ft_strcmp(cur->cmd[0], "unset"))
			{
				builtin_unset(cur->cmd, g_envl);
				return (1);
			}
			else if (ft_strcmp(cur->cmd[0], "exit"))
			{
				builtin_exit(cur->cmd, g_envl);
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
		manage_pipe(cur, next, info->path, pid);
		redirection(cur);
		if (execute_builtin(cur, info, CHILD))
			;
		else if (!check_cmd(cur, info->path))
		{
			printf("🐤AengMuShell: %s: command not found\n", cur->cmd[0]);
			exit(127);
		}
		else
			execute_path(cur, info->path, envp);
	}
	if (pid > 0)
		manage_pipe(cur, next, info->path, pid);
	if (next == NULL)
	{
		waitpid(pid, &status, 0);
		if ((status & 0177) == 0) // return이나 exit으로 종료되었다면,
			set_exit_code(g_envl, (status >> 8) & 0xff);
		else if (((status & 0177) != 0) && ((status & 0177) != 0177))
			set_exit_code(g_envl, 128 + (status & 0177));
		// return이나 exit으로 종료되지 않았고 command not found가 아니라면
		// 128 : fatal error + 시그널 no값을 더해서 표기한다.
	}
}

void	execute(t_process *cur, t_process *next, t_info *info, char **envp)
{
	if (execute_builtin(cur, info, PARENTS))
		;
	else
		execute_program(cur, next, info, envp);
}
