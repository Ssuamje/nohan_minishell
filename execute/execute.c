/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 18:43:15 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	execute_cmd(t_process *cur, t_info *info, char **envp)
{
	redirection(cur, info);
	if (info->err_flag == 0)
	{
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
	exit(1);
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
		execute_cmd(cur, info, envp);
	}
	if (pid > 0)
		manage_pipe(cur, next, info->path, pid);
	if (next == NULL)
	{
		waitpid(pid, &status, 0);
		if ((status & 0177) == 0)
			set_exit_code(g_envl, (status >> 8) & 0xff);
		else if (((status & 0177) != 0) && ((status & 0177) != 0177))
			set_exit_code(g_envl, 128 + (status & 0177));
		init_sighandler();
	}
}

void	execute(t_process *cur, t_process *next, t_info *info, char **envp)
{
	if (execute_builtin(cur, info, PARENTS))
		;
	else
		execute_bin(cur, next, info, envp);
}
