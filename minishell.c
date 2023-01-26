/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/26 23:01:03 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_proc_next(t_proc *proc)
{
	proc->redir_in = NULL;
	// proc->redir_in->flag = IN_APPEND;
	// proc->redir_in->directory = "eof";
	// proc->redir_in->next = NULL;
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "infile.txt";
	// proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = "grep";
	proc->command[1] = "w";
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->next = NULL;
}

void	set_proc(t_proc *proc)
{
	proc->redir_in = NULL;
	// proc->redir_in->flag = IN_TRUNC;
	// proc->redir_in->directory = "infile.txt";
	// proc->redir_in->next = NULL;
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "infile.txt";
	// proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = "cat";
	proc->command[1] = "infile.txt";
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->next = malloc(sizeof(t_proc));
	set_proc_next(proc->next);
}

int	main(int accd, char **av, char **envp)
{
	t_env	env;
	t_fd	fd;
	t_proc	*proc;
	int		status;

	proc = malloc(sizeof(t_proc));
	set_proc(proc);
	env_path(&env);
	while (proc != NULL)
	{
		redirect_in(proc, &fd);
		redirect_out(proc, &fd);
		command(proc, &fd, env.path, envp);
		proc = proc->next;
	}
	return (EXIT_SUCCESS);
}

// gcc *.c ./libft/*.c ./redirection/*.c ./command/*.c -I./includes 