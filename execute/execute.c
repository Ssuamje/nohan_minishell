/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/09 14:44:50 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	execute_cmd(t_process *cur, t_info *info, char **envp)
{
	if (execute_builtin(cur, info, CHILD))
		;
	else if (!check_cmd(cur, info->path, 0))
	{
		printf("AengMuShell: %s: command not found\n", cur->cmd[0]);
		exit(127);
	}
	else
		execute_path(cur, info->path, envp);
}

void	execute_bin(t_process *cur, t_process *next, t_info *info, char **envp)
{
	pid_t	pid;
	int		status;

	set_sigint_to_default();
	pid = fork();
	if (pid == CHILD)
	{
		manage_pipe(cur, next, info->path, pid);
		redirection(cur);
		execute_cmd(cur, info, envp);
	}
	if (pid > 0)
	{
		manage_pipe(cur, next, info->path, pid);
		init_sighandler();
	}
	if (next == NULL)
	{
		waitpid(pid, &status, 0);
		if ((status & 0177) == 0)
			set_exit_code(g_global->g_envl, (status >> 8) & 0xff);
		else if (((status & 0177) != 0) && ((status & 0177) != 0177))
			set_exit_code(g_global->g_envl, 128 + (status & 0177));
	}
}

void	execute(t_process *cur, t_process *next, t_info *info, char **envp)
{
	if (execute_builtin(cur, info, PARENTS))
		;
	else
		execute_bin(cur, next, info, envp);
}
