/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:04:26 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/07 18:49:32 by hyungnoh         ###   ########.fr       */
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
		builtin_export(cur->cmd, g_global->g_envl);
	if (ft_strcmp(builtin, "env"))
		builtin_env(cur->cmd, g_global->g_envl);
	if (ft_strcmp(builtin, "exit"))
		builtin_exit(cur->cmd, g_global->g_envl);
}

int	exec_and_return(char *builtin, t_process *cur)
{
	if (ft_strcmp(builtin, "cd"))
		return (builtin_cd(cur));
	if (ft_strcmp(builtin, "export") && cur->cmd[1] != NULL)
		return (builtin_export(cur->cmd, g_global->g_envl));
	if (ft_strcmp(builtin, "unset"))
		return (builtin_unset(cur->cmd, g_global->g_envl));
	if (ft_strcmp(builtin, "exit"))
	{
		builtin_exit(cur->cmd, g_global->g_envl);
		return (1);
	}
	return (0);
}

int	execute_builtin(t_process *cur, t_info *info, pid_t pid)
{
	if (pid == CHILD)
	{
		exec_and_void(cur->cmd[0], cur);
	}
	if (pid == PARENTS)
	{
		if (info->process_cnt == 1)
			return (exec_and_return(cur->cmd[0], cur));
		else if (ft_strcmp(cur->cmd[0], "export") && cur->cmd[1] != NULL)
			return (1);
		else if (ft_strcmp(cur->cmd[0], "exit"))
			return (0);
		else if (ft_strcmp(cur->cmd[0], "unset"))
			return (1);
	}
	return (0);
}

int	is_binary(char *cmd, char **path)
{
	int		i;
	char	*tmp_cmd;

	i = 0;
	while (cmd[i] != '\0')
		i++;
	i--;
	while (cmd[i] != '/')
		i--;
	i = i + 2;
	tmp_cmd = malloc(sizeof(char) * i);
	ft_strlcpy(tmp_cmd, cmd, (size_t)i);
	i = -1;
	while (path[++i])
	{
		if (ft_strcmp(path[i], tmp_cmd))
		{
			free(tmp_cmd);
			return (1);
		}
	}
	free(tmp_cmd);
	return (0);
}

int	permission_check(char *cmd, char **path)
{
	int			mode;
	char		*err_msg;
	struct stat	sb;

	mode = R_OK | W_OK | X_OK;
	if (access(cmd, mode) == 0 && stat(cmd, &sb) == 0)
	{
		if ((S_IFMT & sb.st_mode) == S_IFREG)
			exit(0);
	}
	if (stat(cmd, &sb) == 0 && is_binary(cmd, path))
		return (1);
	if (ft_strchr(cmd, '/') && stat(cmd, &sb) != 0)
	{
		err_msg = ft_strjoin("AengMuShell: ", cmd);
		perror(err_msg);
		free(err_msg);
		exit(127);
	}
	else if (ft_strchr(cmd, '/') && stat(cmd, &sb) == 0)
	{
		if ((S_IFMT & sb.st_mode) != S_IFREG)
		{		
			ft_putstr_fd("AengMuShell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
	}
	err_msg = ft_strjoin("AengMuShell: ", cmd);
	perror(err_msg);
	free(err_msg);
	exit(126);
}
