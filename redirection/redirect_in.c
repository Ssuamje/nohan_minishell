/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 18:19:22 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

static void	in_trunc(t_process *proc, t_redir *redir, t_info *info)
{
	struct stat	sb;

	if (stat(redir->file, &sb) == 0)
	{
		proc->fd_infile = open(redir->file, O_RDONLY);
		dup2(proc->fd_infile, STDIN_FILENO);
		close(proc->fd_infile);
	}
	else
	{
		info->err_flag = 1;
		printf("AengMuShell: %s: No such file or directory\n", redir->file);
	}
}

static void	in_append(t_process *proc, t_redir *redir, t_info *info)
{
	struct stat	sb;

	if (stat(redir->file, &sb) == 0)
	{
		proc->fd_infile = open(redir->file, O_RDONLY);
		dup2(proc->fd_infile, STDIN_FILENO);
		close(proc->fd_infile);
		unlink(redir->file);
	}
	else
	{
		info->err_flag = 1;
		printf("AengMuShell: %s: No such file or directory\n", redir->file);
	}
}

void	redirect_in(t_process *proc, t_info *info)
{
	t_list	*tmp;
	t_redir	*tmp_redir;

	tmp = proc->redir_in->next;
	while (tmp != NULL && tmp->content != NULL && info->err_flag == 0)
	{
		tmp_redir = tmp->content;
		if (tmp_redir->flag == IN_TRUNC)
			in_trunc(proc, tmp_redir, info);
		else if (tmp_redir->flag == IN_APPEND)
			in_append(proc, tmp_redir, info);
		tmp = tmp->next;
	}
}
