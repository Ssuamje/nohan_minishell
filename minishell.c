/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/20 16:00:12 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_proc(t_proc *proc)
{
	proc->redir_in = malloc(sizeof(t_redir) * 1);
	proc->redir_in->flag = IN_TRUNC;
	proc->redir_in->directory = "infile.txt";
	proc->redir_in->next = NULL;
	proc->redir_out = malloc(sizeof(t_redir) * 1);
	proc->redir_out->flag = OUT_TRUNC;
	proc->redir_out->directory = "outfile.txt";
	proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 3);
	proc->command[0] = "echo";
	proc->command[1] = "hello we are nohan team!";
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