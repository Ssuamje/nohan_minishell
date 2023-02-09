/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/09 15:18:24 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "readline/readline.h"
#include "../include/prompt.h"

void	heredoc_sighandler(int signo)
{
	printf("\n");
	if (signo == SIGINT)
	{
		write(1, "> Press Enter To Exit", 21);
		g_global->g_sigint_flag = TRUE;
		set_exit_code(g_global->g_envl, 1);
	}
}

static void	create_heredoc_tmp(t_redir *redir, t_process *proc)
{
	char		*buffer;

	signal(SIGINT, heredoc_sighandler);
	while (1)
	{
		buffer = readline("🐦 > ");
		if (g_global->g_sigint_flag == TRUE)
		{
			free(buffer);
			buffer = NULL;
		}
		if (buffer == NULL)
			break ;
		if (ft_strcmp(buffer, redir->file))
		{
			free(buffer);
			break ;
		}
		if (count_dollar_sign(buffer) > 0)
			interpret_buffer_env(&buffer);
		ft_putstr_fd(buffer, proc->fd_infile);
		ft_putstr_fd("\n", proc->fd_infile);
		free(buffer);
	}
	g_global->g_sigint_flag = FALSE;
}

static void	exec_heredoc(t_redir *redir, t_process *proc, int *idx)
{
	char	*heredoc;
	char	*idx_tmp;

	(*idx)++;
	idx_tmp = ft_itoa(*idx);
	heredoc = ft_join_and_free(ft_strdup("/tmp/heredoc"), idx_tmp);
	proc->fd_infile = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	create_heredoc_tmp(redir, proc);
	set_sigint_to_default();
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
