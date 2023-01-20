/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/20 14:00:16 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	in_trunc(t_redir *redir, t_fd *fd)
{
	fd->infile = open(redir->directory, O_RDONLY);
	dup2(fd->infile, STDIN_FILENO);
}

static void	in_append(t_redir *redir, t_fd *fd)
{
	fd->infile = open(redir->directory, O_RDONLY);
	dup2(fd->infile, STDIN_FILENO);
}

void	redirect_in(t_proc *proc, t_fd *fd)
{
	while (proc->redir_in)
	{
		if (proc->redir_in->flag == IN_TRUNC)
			in_trunc(proc->redir_in, fd);
		if (proc->redir_in->flag == IN_APPEND)
			in_append(proc->redir_in, fd);
		proc->redir_in = proc->redir_in->next;
	}
}
