/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 19:39:45 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "../builtin/cd/cd.h"

static void	in_trunc(t_process *proc, t_redir *redir, t_info *info)
{
	struct stat	sb;
	int			mode;

	mode = R_OK;
	if (stat(redir->file, &sb) == 0)
	{
		if (access(redir->file, mode) == 0)
		{
			proc->fd_infile = open(redir->file, O_RDONLY);
			dup2(proc->fd_infile, STDIN_FILENO);
			close(proc->fd_infile);
		}
		else
		{
			info->err_flag = 1;
			printf("AengMuShell: %s: Permission denied\n", redir->file);	
		}
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
	int			mode;

	mode = R_OK;
	if (stat(redir->file, &sb) == 0)
	{
		if (access(redir->file, mode) == 0)
		{
			proc->fd_infile = open(redir->file, O_RDONLY);
			dup2(proc->fd_infile, STDIN_FILENO);
			close(proc->fd_infile);
		}
		else
		{
			info->err_flag = 1;
			printf("AengMuShell: %s: Permission denied\n", redir->file);	
		}
	}
	else
	{
		info->err_flag = 1;
		printf("AengMuShell: %s: No such file or directory\n", redir->file);
	}
}

static void	interpret_redir_file(t_redir *redir)
{
	char	*tmp;

	if (ft_strncmp(redir->file, "~/", 2) == 0)
	{
		tmp = redir->file;
		redir->file = ft_join_and_free(get_value_by_key(g_envl, "HOME"), \
				ft_join_and_free(ft_strdup("/"), ft_strdup(&(redir->file[2]))));
		free(tmp);
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
		interpret_redir_file(tmp_redir);
		if (tmp_redir->flag == IN_TRUNC)
			in_trunc(proc, tmp_redir, info);
		else if (tmp_redir->flag == IN_APPEND)
			in_append(proc, tmp_redir, info);
		tmp = tmp->next;
	}
}
