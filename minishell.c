/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 19:55:31 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_proc_next3(t_proc *proc)
{
	proc->redir_in = malloc(sizeof(t_redir));
	proc->redir_in->flag = IN_APPEND;
	proc->redir_in->directory = "eof4";
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "infile.txt";
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = NULL;
	proc->command[1] = NULL;
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->heredoc = ft_strdup("3");
	proc->next = NULL;
}

void	set_proc_next2(t_proc *proc)
{
	proc->redir_in = malloc(sizeof(t_redir));
	proc->redir_in->flag = IN_APPEND;
	proc->redir_in->directory = "eof3";
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "infile.txt";
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = NULL;
	proc->command[1] = NULL;
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->heredoc = ft_strdup("2");
	proc->next = malloc(sizeof(t_proc));
	set_proc_next3(proc->next);
}

void	set_proc_next(t_proc *proc)
{
	proc->redir_in = malloc(sizeof(t_redir));
	proc->redir_in->flag = IN_APPEND;
	proc->redir_in->directory = "eof2";
	proc->redir_out = NULL;
	// proc->redir_out->flag = OUT_TRUNC;
	// proc->redir_out->directory = "infile.txt";
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = NULL;
	proc->command[1] = NULL;
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->heredoc = ft_strdup("1");
	proc->next = NULL;
	// set_proc_next2(proc->next);
}

void	set_proc(t_proc *proc)
{
	proc->redir_in = NULL;
	// proc->redir_in->flag = IN_APPEND;
	// proc->redir_in->directory = ft_strdup("eof");
	proc->redir_out = malloc(sizeof(t_redir));
	proc->redir_out->flag = OUT_TRUNC;
	proc->redir_out->directory = "infile.txt";
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = "ls";
	proc->command[1] = "-lra";
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->heredoc = ft_strdup("0");
	proc->next = NULL;
	// set_proc_next(proc->next);
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;
	t_proc	*proc;
	int		stdfd[2];
	int		pfd[2];
	int		status;
	int		child_size;

	proc = malloc(sizeof(t_proc)); //setting
	set_proc(proc); //setting
	env_path(&env, envp); // setting

	child_size = get_child_size(proc);
	stdfd[0] = dup(STDIN_FILENO);
	stdfd[1] = dup(STDOUT_FILENO);
	while (proc != NULL)
	{	
		pipe(pfd);
		execute(proc, pfd, env.path, envp);
		proc = proc->next;
	}
	while (--child_size)
		wait(&status);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
}

// gcc *.c ./libft/*.c ./redirection/*.c ./command/*.c -I./includes 