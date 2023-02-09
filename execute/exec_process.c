/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/09 13:54:45 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	process_dup_pipe(t_list *procs, t_info *info, char **envp)
{
	t_list		*tmp;
	t_process	*cur;
	int			status;

	set_heredoc_fd(procs);
	info->process_cnt = ft_lstsize(procs) - 1;
	tmp = procs->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur = tmp->content;
		interpret_cur_file(cur);
		pipe(cur->pfd);
		if (tmp->next == NULL)
			execute(cur, NULL, info, envp);
		else
			execute(cur, tmp->next->content, info, envp);
		tmp = tmp->next;
	}
	while (--(info->process_cnt))
		wait(&status);
}

void	exec_process(char **envp, t_list *procs)
{
	t_info	info;

	info.stdfd[0] = dup(STDIN_FILENO);
	info.stdfd[1] = dup(STDOUT_FILENO);
	env_path(&info, envp);
	process_dup_pipe(procs, &info, envp);
	dup2(info.stdfd[0], STDIN_FILENO);
	dup2(info.stdfd[1], STDOUT_FILENO);
	close(info.stdfd[0]);
	close(info.stdfd[1]);
	if (info.path != NULL)
		free_split(info.path);
}
