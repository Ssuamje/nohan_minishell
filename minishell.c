/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/23 13:08:44 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_proc(t_proc *proc)
{
	proc->redir_in = malloc(sizeof(t_redir) * 1);
	proc->redir_in->flag = IN_APPEND;
	proc->redir_in->directory = "eof";
	proc->redir_in->next = NULL;
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "outfile.txt";
	// proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 3);
	proc->command[0] = "cat";
	proc->command[1] = NULL;
	proc->command[2] = NULL;
	proc->next = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;
	t_fd	fd;
	t_proc	proc;

	set_proc(&proc);
	env_path(&env);
	redirect_in(&proc, &fd);
	redirect_out(&proc, &fd);
	command(&proc, &fd, env.path, envp);
	return (EXIT_SUCCESS);
}

// gcc *.c ./libft/*.c ./redirection/*.c ./command/*.c -I./includes 