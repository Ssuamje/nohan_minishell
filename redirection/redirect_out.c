/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:57:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/01 16:07:13 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

static void	out_trunc(t_process *proc, t_redir *redir)
{
	proc->fd_outfile = open(redir->file, \
						O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(proc->fd_outfile, STDOUT_FILENO);
	close(proc->fd_outfile);
}

static void	out_append(t_process *proc, t_redir *redir)
{
	proc->fd_outfile = open(redir->file, \
						O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(proc->fd_outfile, STDOUT_FILENO);
	close(proc->fd_outfile);
}

void	redirect_out(t_process *proc)
{
	t_list	*tmp;
	t_redir *tmp_redir;

	tmp = proc->redir_out->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		tmp_redir = tmp->content;
		if (tmp_redir->flag == OUT_TRUNC)
			out_trunc(proc, tmp_redir);
		else if (tmp_redir->flag == OUT_APPEND)
			out_append(proc, tmp_redir);
		tmp = tmp->next;
	}
}
