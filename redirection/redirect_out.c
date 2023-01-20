/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:57:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/20 15:57:16 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	out_trunc(t_redir *redir, t_fd *fd)
{
	fd->outfile = open(redir->directory, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(fd->outfile, STDOUT_FILENO);
	close(fd->outfile);
}

static void	out_append(t_redir *redir, t_fd *fd)
{
	fd->outfile = open(redir->directory, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(fd->outfile, STDOUT_FILENO);
	close(fd->outfile);
}

void	redirect_out(t_proc *proc, t_fd *fd)
{
	while (proc->redir_out)
	{
		if (proc->redir_out->flag == OUT_TRUNC)
			out_trunc(proc->redir_out, fd);
		if (proc->redir_out->flag == OUT_APPEND)
			out_append(proc->redir_out, fd);
		proc->redir_out = proc->redir_out->next;
	}
}
