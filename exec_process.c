/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/03 01:08:52 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	process_dup_pipe(t_list *procs, char **path, char **envp, int stdfd[])
{
	t_list		*tmp;
	t_process	*cur;
	int			status;
	int			child_cnt;

	set_heredoc_fd(procs, stdfd);
	tmp = procs->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur = tmp->content;
		pipe(cur->pfd);
		if (tmp->next == NULL)
			execute(cur, NULL, path, envp);
		else
			execute(cur, tmp->next->content, path, envp);
		tmp = tmp->next;
	}
	child_cnt = ft_lstsize(procs) - 1;
	while (--child_cnt)
		wait(&status);
}

void	exec_process(char **envp, t_list *procs)
{
	t_env	env;
	int		stdfd[2];

	stdfd[0] = dup(STDIN_FILENO);
	stdfd[1] = dup(STDOUT_FILENO);
	env_path(&env, envp);
	process_dup_pipe(procs, env.path, envp, stdfd);
	free_env_path(&env);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
}

// gcc prompt.c ./parser/tokenizer/*.c ./parser/lexer/*.c -I ./include ./libft/*.c ./error/error.c ./parser/*.c ./execute/execute.c ./redirection/*.c exec_process.c env_path.c ./envl/*.c ./utils/*.c -lreadline