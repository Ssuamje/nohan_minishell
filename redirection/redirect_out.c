/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:57:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 21:10:03 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "../builtin/cd/cd.h"

static void	out_trunc(t_process *proc, t_redir *redir, t_info *info)
{
	struct stat	sb;
	int			mode;

	mode = R_OK | W_OK;

	proc->fd_outfile = open(redir->file, \
						O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644) < 0)
	{
		perror(redir->file);
		exit(1);
	}
	if (stat(redir->file, &sb) == 0)
	{
		if (S_ISREG(sb.st_mode) && access(redir->file, mode) == 0)
		{
			proc->fd_outfile = open(redir->file, \
								O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(proc->fd_outfile, STDOUT_FILENO);
			close(proc->fd_outfile);
		}
		else if (S_ISDIR(sb.st_mode))
		{
			info->err_flag = 1;
			printf("bash: %s: Is a directory\n", redir->file);
		}
	}
	else if (stat(redir->file, &sb) != 0 && access(redir->file, mode) != 0 && redir->file[0] != '/')
	{
		proc->fd_outfile = open(redir->file, \
							O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(proc->fd_outfile, STDOUT_FILENO);
		close(proc->fd_outfile);
	}
	else
	{
		info->err_flag = 1;
		printf("bash: %s: Permission denied\n", redir->file);
	}
}

static void	out_append(t_process *proc, t_redir *redir, t_info *info)
{
	struct stat	sb;
	int			mode;

	mode = R_OK | W_OK;
	if (access(redir->file, mode) == 0 && stat(redir->file, &sb) == 0)
	{
		proc->fd_outfile = open(redir->file, \
							O_RDWR | O_CREAT | O_APPEND, 0644);
		dup2(proc->fd_outfile, STDOUT_FILENO);
		close(proc->fd_outfile);
	}
	else if (stat(redir->file, &sb) != 0 && redir->file[0] != '/')
	{
		proc->fd_outfile = open(redir->file, \
							O_RDWR | O_CREAT | O_APPEND, 0644);
		dup2(proc->fd_outfile, STDOUT_FILENO);
		close(proc->fd_outfile);
	}
	else
	{
		info->err_flag = 1;
		printf("bash: %s: Permission denied\n", redir->file);
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

void	redirect_out(t_process *proc, t_info *info)
{
	t_list	*tmp;
	t_redir	*tmp_redir;

	(void)info;
	tmp = proc->redir_out->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		tmp_redir = tmp->content;
		interpret_redir_file(tmp_redir);
		if (tmp_redir->flag == OUT_TRUNC)
			out_trunc(proc, tmp_redir, info);
		else if (tmp_redir->flag == OUT_APPEND)
			out_append(proc, tmp_redir, info);
		tmp = tmp->next;
	}
}
