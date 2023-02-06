/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:04:26 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 16:04:56 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

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

void	exec_and_void(char *builtin, t_process *cur)
{
	if (ft_strcmp(builtin, "echo"))
		builtin_echo(cur);
	if (ft_strcmp(builtin, "pwd"))
		builtin_pwd();
	if (ft_strcmp(builtin, "export") && cur->cmd[1] == NULL)
		builtin_export(cur->cmd, g_envl);
	if (ft_strcmp(builtin, "env"))
		builtin_env(cur->cmd, g_envl);
}

int	exec_and_return(char *builtin, t_process *cur)
{
	if (ft_strcmp(builtin, "cd"))
		return (builtin_cd(cur));
	if (ft_strcmp(builtin, "export") && cur->cmd[1] != NULL)
		return (builtin_export(cur->cmd, g_envl));
	if (ft_strcmp(builtin, "unset"))
		return (builtin_unset(cur->cmd, g_envl));
	if (ft_strcmp(builtin, "exit"))
	{
		builtin_exit(cur->cmd, g_envl);
		return (1);
	}
	return (0);
}

int	execute_builtin(t_process *cur, t_info *info, pid_t pid)
{
	if (pid == CHILD)
		exec_and_void(cur->cmd[0], cur);
	if (pid == PARENTS)
	{	
		if (info->process_cnt == 1)
			return (exec_and_return(cur->cmd[0], cur));
		else if (ft_strcmp(cur->cmd[0], "export") && cur->cmd[1] != NULL)
			return (1);
		else if (ft_strcmp(cur->cmd[0], "exit"))
			return (1);
		else if (ft_strcmp(cur->cmd[0], "unset"))
			return (1);
	}
	return (0);
}
