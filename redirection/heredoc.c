/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/05 18:23:04 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "readline/readline.h"

static void	create_heredoc_tmp(t_redir *redir)
{
	char		*buffer;
	size_t		buffer_len;

	// signal(SIGQUIT, sighandler2);
	while (1)
	{
		buffer = ft_calloc(sizeof(char), 1024);
		if (buffer == NULL)
			exit_error(ERR_MALLOC);
		if (read(0, buffer, 1024) == 0)
		{
			free(buffer);
			break ;
		}
		buffer_len = 0;
		while (buffer[buffer_len] != '\n')
			buffer_len++;
		if (!ft_strncmp(buffer, redir->file,
				ft_strlen(redir->file)) && buffer_len == ft_strlen(redir->file))
		{
			free(buffer);
			break ;
		}
		buffer[buffer_len + 1] = '\0';
		ft_putstr(buffer);
		free(buffer);
	}
}

static void	exec_heredoc(t_redir *redir, t_process *proc, int *idx)
{
	char	*heredoc;
	char	*idx_tmp;

	(*idx)++;
	idx_tmp = ft_itoa(*idx);
	heredoc = ft_join_and_free(ft_strdup("/tmp/heredoc"), idx_tmp);
	proc->fd_infile = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(proc->fd_infile, STDOUT_FILENO);
	close(proc->fd_infile);
	create_heredoc_tmp(redir);
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

void	set_heredoc_fd(t_list *procs, int stdfd[])
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
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
}

// rl_catch_signals