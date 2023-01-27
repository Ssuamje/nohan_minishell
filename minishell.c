/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/27 16:33:58 by hyungnoh         ###   ########.fr       */
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
	// proc->redir_out->directory = "outfile.txt";
	// proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 4);
	proc->command[0] = "wc";
	proc->command[1] = "-l";
	proc->command[2] = NULL;
	proc->command[3] = NULL;
	proc->next = NULL;
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
	proc->next = malloc(sizeof(t_proc));
	set_proc_next(proc->next);
}

int	main(int accd, char **av, char **envp)
{
	t_env	env;
	t_fd	fd;
	t_proc	*proc;
	int		pfd[2];
	int		status;
	pid_t	pid;

	proc = malloc(sizeof(t_proc));
	set_proc(proc);
	env_path(&env);
	while (proc != NULL)
	{
		redirect_in(proc, &fd);
		redirect_out(proc, &fd);
		pipe(pfd);
		pid = fork();
		if (pid == 0)
		{	
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
		}
		else
		{
			close(pfd[0]);
			dup2(pfd[1], STDOUT_FILENO);
			command(proc, &fd, env.path, envp);
		}
		proc = proc->next;
	}
	close(pfd[0]);
	close(pfd[1]);
	return (EXIT_SUCCESS);
}

// gcc *.c ./libft/*.c ./redirection/*.c ./command/*.c -I./includes 