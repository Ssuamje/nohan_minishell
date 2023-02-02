/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/02 13:42:20 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	check(void)
{
	system("leaks a.out");
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
}

// gcc *.c ./libft/*.c ./redirection/*.c ./command/*.c -I./includes 