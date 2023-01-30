/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:57:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/30 18:59:41 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	out_trunc(t_proc *proc)
{
	proc->outfile = open(proc->redir_out->directory, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(proc->outfile, STDOUT_FILENO);
	close(proc->outfile);
}

static void	out_append(t_proc *proc)
{
	proc->outfile = open(proc->redir_out->directory, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(proc->outfile, STDOUT_FILENO);
	close(proc->outfile);
}

void	redirect_out(t_proc *proc)
{
	while (proc->redir_out)
	{
		if (proc->redir_out->flag == OUT_TRUNC)
			out_trunc(proc);
		if (proc->redir_out->flag == OUT_APPEND)
			out_append(proc);
		proc->outfile_exist = 1;
		proc->redir_out = proc->redir_out->next;
	}
}
