/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/02 23:32:00 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	check(void)
{
	system("leaks a.out");
}

void	process_dup_pipe(t_list *procs, char **path, char **envp, int stdfd[])
{
	t_list		*tmp1;
	t_list		*tmp2;
	t_process	*cur_proc;
	int			pfd[2];

	tmp1 = procs->next;
	tmp2 = procs->next;
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
		pipe(cur_proc->pfd);
		if (tmp2->next == NULL)
			execute(cur_proc, NULL, path, envp);
		else
			execute(cur_proc, tmp2->next->content, path, envp);
		tmp2 = tmp2->next;
	}
}

void	exec_process(char **envp, t_list *procs)
{
	t_env	env;
	int		stdfd[2];
	int		status;
	int		child_size;

	stdfd[0] = dup(STDIN_FILENO);
	stdfd[1] = dup(STDOUT_FILENO);
	env_path(&env, envp);
	child_size = ft_lstsize(procs) - 1;
	process_dup_pipe(procs, env.path, envp, stdfd);
	while (--child_size)
		wait(&status);
	free_env_path(&env);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
}

// gcc prompt.c ./parser/tokenizer/*.c ./parser/lexer/*.c -I ./include ./libft/*.c ./error/error.c ./parser/*.c ./execute/execute.c ./redirection/*.c exec_process.c env_path.c ./envl/*.c ./utils/*.c -lreadline