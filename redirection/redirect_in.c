/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/07 00:29:47 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

static void	in_trunc(t_process *proc, t_redir *redir)
{
	proc->fd_infile = open(redir->file, O_RDONLY);
	if (proc->fd_infile == OPEN_ERROR)
	{
		perror(redir->file);
		exit(1);
	}
	dup2(proc->fd_infile, STDIN_FILENO);
	close(proc->fd_infile);
}

static void	in_append(t_process *proc, t_redir *redir)
{
	proc->fd_infile = open(redir->file, O_RDONLY);
	if (proc->fd_infile == OPEN_ERROR)
	{
		unlink(redir->file);
		perror(redir->file);
		exit(1);
	}
	dup2(proc->fd_infile, STDIN_FILENO);
	close(proc->fd_infile);
	unlink(redir->file);
}

void	redirect_in(t_process *proc)
{
	t_list	*tmp;
	t_redir	*tmp_redir;

	tmp = proc->redir_in->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		tmp_redir = tmp->content;
		if (tmp_redir->flag == IN_TRUNC)
			in_trunc(proc, tmp_redir);
		else if (tmp_redir->flag == IN_APPEND)
			in_append(proc, tmp_redir);
		tmp = tmp->next;
	}
}
