/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:50:32 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/04 13:01:57 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	env_command(t_process *cur_proc, t_process *next_proc, int pfd[], char **path, char **envp)
{
	int		i;
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
		i = -1;
		while (path[++i])
		{
			full_path = ft_strjoin(path[i], cur_proc->cmd[0]);
			free(path[i]);
			execve(full_path, cur_proc->cmd, envp);
		}
		exit(0);
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

void	pipe_process(t_list *processes, int *pfd, char **env_path, char **envp, int stdfd[])
{
	t_list		*tmp1;
	t_list		*tmp2;
	t_process	*cur_proc;

	tmp1 = processes->next;
	tmp2 = processes->next;
	while (tmp1 != NULL && tmp1->content != NULL)
	{
		cur_proc = tmp1->content;
		heredoc(cur_proc);
		tmp1 = tmp1->next;
	}
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
	while (tmp2 != NULL && tmp2->content != NULL)
	{
		cur_proc = tmp2->content;
		pipe(pfd);
		if (tmp2->next == NULL)
			execute(cur_proc, NULL, pfd, env_path, envp);
		else
			execute(cur_proc, tmp2->next->content, pfd, env_path, envp);
		tmp2 = tmp2->next;
	}
}

void	exec_process(char **envp, t_list *processes)
{
	t_env	env;
	int		stdfd[2];
	int		pfd[2];
	int		status = -1;
	int		child_size;

	env_path(&env, envp);
	child_size = ft_lstsize(processes) - 1;
	stdfd[0] = dup(STDIN_FILENO);
	stdfd[1] = dup(STDOUT_FILENO);
	pipe_process(processes, pfd, env.path, envp, stdfd);
	while (--child_size)
		wait(&status);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
	free_env_path(&env);
}
