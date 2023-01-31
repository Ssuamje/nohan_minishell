/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 20:53:25 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	check(void)
{
	system("leaks a.out");
}

void	pipe_process(t_list *processes, int *pfd, char **env_path, char **envp)
{
	t_list		*tmp;
	t_process	*cur_proc;

	tmp = processes->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur_proc = tmp->content;
		pipe(pfd);
		execute(cur_proc, tmp->next->content, pfd, env_path, envp);
		tmp = tmp->next;
	}
}

void	exec_process(char **envp, t_list *processes)
{
	t_env	env;
	int		stdfd[2];
	int		pfd[2];
	int		status;
	int		child_size;

	// atexit(check);
	env_path(&env, envp); // setting

	child_size = ft_lstsize(processes - 1);
	stdfd[0] = dup(STDIN_FILENO);
	stdfd[1] = dup(STDOUT_FILENO);
	pipe_process(processes, pfd, env.path, envp);
	while (--child_size)
		wait(&status);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
}

// gcc *.c ./libft/*.c ./redirection/*.c ./command/*.c -I./includes 