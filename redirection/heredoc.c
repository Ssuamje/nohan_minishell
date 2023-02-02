/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/02 13:50:23 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

static void	exec_heredoc(t_redir *redir, t_process *proc)
{
	char		*buffer;
	size_t		buffer_len;
	static int	idx;
	char		heredoc[2];

	idx++;
	heredoc[0] = idx + 48;
	heredoc[1] = '\0';
	proc->fd_infile = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(proc->fd_infile, STDOUT_FILENO);
	close(proc->fd_infile);
	while (1)
	{
		buffer = malloc(sizeof(char) * 1000);
		read(0, buffer, 1000);
		buffer_len = 0;
		while (buffer[buffer_len] != '\n')
			buffer_len++;
		if (!ft_strncmp(buffer, redir->file,
				ft_strlen(redir->file)) && buffer_len == ft_strlen(redir->file))
		{
			free(buffer);
			break ;
		}
		ft_putstr(buffer);
		free(buffer);
	}
	free(redir->file);
	redir->file = ft_strdup(heredoc);
}

void	heredoc(t_process *proc)
{
	t_list	*tmp;
	t_redir *tmp_redir;

	tmp = proc->redir_in->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		tmp_redir = tmp->content;
		if (tmp_redir->flag == IN_APPEND)
			exec_heredoc(tmp_redir, proc);
		tmp = tmp->next;
	}
}
