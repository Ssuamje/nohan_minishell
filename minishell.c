/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/30 21:49:32 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_proc_next3(t_proc *proc)
{
	proc->redir_in = NULL;
	// proc->redir_in->flag = IN_APPEND;
	// proc->redir_in->directory = "eof";
	// proc->redir_in->next = NULL;
	proc->redir_out = malloc(sizeof(t_redir));
	proc->redir_out->flag = OUT_TRUNC;
	proc->redir_out->directory = "outfile.txt";
	proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = "cat";
	proc->command[1] = "-e";
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->next = NULL;
}

void	set_proc_next2(t_proc *proc)
{
	proc->redir_in = NULL;
	// proc->redir_in->flag = IN_APPEND;
	// proc->redir_in->directory = "eof";
	// proc->redir_in->next = NULL;
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "outfile.txt";
	// proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = "grep";
	proc->command[1] = "w";
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->next = malloc(sizeof(t_proc));
	proc->next->prev = proc;
	set_proc_next3(proc->next);
}

void	set_proc_next(t_proc *proc)
{
	proc->redir_in = NULL;
	// proc->redir_in->flag = IN_APPEND;
	// proc->redir_in->directory = "eof";
	// proc->redir_in->next = NULL;
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "outfile.txt";
	// proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = "cat";
	proc->command[1] = "-e";
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->next = malloc(sizeof(t_proc));
	proc->next->prev = proc;
	set_proc_next2(proc->next);
}

void	set_proc(t_proc *proc)
{
	proc->redir_in = malloc(sizeof(t_redir));
	proc->redir_in->flag = IN_APPEND;
	proc->redir_in->directory = "eof";
	proc->redir_in->next = NULL;
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "infile.txt";
	// proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = "cat";
	proc->command[1] = NULL;
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->prev = NULL;
	proc->next = malloc(sizeof(t_proc));
	proc->next->prev = proc;
	set_proc_next(proc->next);
}

int	main(int accd, char **av, char **envp)
{
	t_env	env;
	t_proc	*proc;
	int		stin;
	int		stout;

	proc = malloc(sizeof(t_proc)); //setting
	set_proc(proc); //setting
	env_path(&env); // setting

	while (proc != NULL)
	{	
		stin = dup(STDIN_FILENO);
		stout = dup(STDOUT_FILENO);
		execute(proc, env.path, envp);
		if (proc->next != NULL)
			close(proc->next->pip[1]);
		dup2(stin, STDIN_FILENO);
		dup2(stout, STDOUT_FILENO);
		close(stin);
		close(stout);
		proc = proc->next;
	}
}

// gcc *.c ./libft/*.c ./redirection/*.c ./command/*.c -I./includes 