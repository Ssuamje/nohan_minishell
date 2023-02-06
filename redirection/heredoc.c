/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 14:16:05 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "readline/readline.h"

static void	create_heredoc_tmp(t_redir *redir, t_process *proc)
{
	char		*buffer;

	while (1)
	{
		buffer = readline("🐦 > ");
		if (buffer == NULL)
		{
			free(buffer);
			break ;
		}
		if (ft_strcmp(buffer, redir->file))
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, proc->fd_infile);
		ft_putstr_fd("\n", proc->fd_infile);
		free(buffer);
	}
}

static void	exec_heredoc(t_redir *redir, t_process *proc, int *idx)
{
	char	*heredoc;
	char	*idx_tmp;

	(*idx)++;
	idx_tmp = ft_itoa(*idx);
	heredoc = ft_join_and_free(ft_strdup("heredoc"), idx_tmp);
	proc->fd_infile = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	create_heredoc_tmp(redir, proc);
	free(redir->file);
	redir->file = ft_strdup(heredoc);
	free(heredoc);
}

void	heredoc(t_process *proc, int *idx)
{
	t_list		*tmp;
	t_redir		*tmp_redir;

	tmp = proc->redir_in->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		tmp_redir = tmp->content;
		if (tmp_redir->flag == IN_APPEND)
			exec_heredoc(tmp_redir, proc, idx);
		tmp = tmp->next;
	}
}

void	set_heredoc_fd(t_list *procs)
{
	t_list		*tmp;
	t_process	*cur;
	static int	idx;

	tmp = procs->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur = tmp->content;
		heredoc(cur, &idx);
		tmp = tmp->next;
	}
	idx = 0;
}
