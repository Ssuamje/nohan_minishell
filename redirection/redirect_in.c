/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 19:51:53 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	in_trunc(t_proc *proc)
{
	proc->infile = open(proc->redir_in->directory, O_RDONLY);
	dup2(proc->infile, STDIN_FILENO);
	close(proc->infile);
}

static void	heredoc(t_proc *proc)
{
	int		buffer_fd;
	char	*buffer;
	int		old_fd;
	int		buffer_len;

	old_fd = dup(STDOUT_FILENO);
	buffer_fd = open(proc->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(buffer_fd, STDOUT_FILENO);
	close(buffer_fd);
	while (1)
	{
		buffer = malloc(sizeof(char) * 1000);
		read(0, buffer, 1000);
		buffer_len = 0;
		while (buffer[buffer_len] != '\n')
			buffer_len++;
		if (!ft_strncmp(buffer, proc->redir_in->directory,
				ft_strlen(proc->redir_in->directory)) && buffer_len == ft_strlen(proc->redir_in->directory))
		{
			free(buffer);
			break ;
		}
		ft_putstr(buffer);
		free(buffer);
	}
	dup2(old_fd, STDOUT_FILENO);
	buffer_fd = open(proc->heredoc, O_RDONLY);
	dup2(buffer_fd, STDIN_FILENO);
	close(buffer_fd);
}

void	redirect_in(t_proc *proc)
{
	if (proc->redir_in != NULL)
	{
		if (proc->redir_in->flag == IN_TRUNC)
			in_trunc(proc);
		else if (proc->redir_in->flag == IN_APPEND)
			heredoc(proc);
	}
}
