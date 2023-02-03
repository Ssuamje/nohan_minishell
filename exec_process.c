/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/03 18:42:09 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	process_dup_pipe(t_list *procs, t_info *info, char **envp, int stdfd[])
{
	t_list		*tmp;
	t_process	*cur;
	int			status;

	set_heredoc_fd(procs, stdfd);
	info->pipe_cnt = ft_lstsize(procs) - 1;
	tmp = procs->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur = tmp->content;
		pipe(cur->pfd);
		if (tmp->next == NULL)
			execute(cur, NULL, info, envp);
		else
			execute(cur, tmp->next->content, info, envp);
		tmp = tmp->next;
	}
	while (--(info->pipe_cnt))
		wait(&status);
}

void	exec_process(char **envp, t_list *procs)
{
	t_info	info;
	int		stdfd[2];

	stdfd[0] = dup(STDIN_FILENO);
	stdfd[1] = dup(STDOUT_FILENO);
	env_path(&info, envp);
	process_dup_pipe(procs, &info, envp, stdfd);
	free_split(envp);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
}

// gcc prompt*.c ./parser/tokenizer/*.c ./parser/lexer/*.c -I ./include ./libft/*.c ./error/error.c ./parser/*.c exec_process.c env_path.c ./execute/execute.c ./redirection/*.c ./envl/*.c ./utils/*.c  ./builtin/export/*.c ./builtin/unset/*.c ./builtin/echo/*.c ./builtin/pwd/*.c ./builtin/cd/*.c -lreadline