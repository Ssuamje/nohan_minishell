/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:25:16 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/20 13:18:07 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_proc(t_proc *proc)
{
	proc->redir_in = NULL;
	proc->redir_out = malloc(sizeof(t_redir) * 1);
	proc->redir_out->flag = OUT_TRUNC;
	proc->redir_out->directory = "outfile.txt";
	proc->redir_out->next = NULL;
	proc->command = malloc(sizeof(char *) * 3);
	proc->command[0] = "cat";
	proc->command[1] = "infile.txt";
	proc->command[2] = NULL;
	proc->next = NULL;
}

int	main(int ac, char **av, char **envp)
{
	char	**path;
	t_fd	fd;
	t_proc	proc;

	set_proc(&proc);
	env_path(path);
	redirect_in(&proc, &fd);
	redirect_out(&proc, &fd);
	command(&proc, &fd, path, envp);
	return (EXIT_SUCCESS);
}
