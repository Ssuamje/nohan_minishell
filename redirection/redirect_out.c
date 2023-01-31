/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:57:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 16:49:46 by hyungnoh         ###   ########.fr       */
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
	if (proc->redir_out != NULL)
	{
		if (proc->redir_out->flag == OUT_TRUNC)
			out_trunc(proc);
		else if (proc->redir_out->flag == OUT_APPEND)
			out_append(proc);
	}
}
