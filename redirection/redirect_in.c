/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/26 13:17:10 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static void	in_trunc(t_redir *redir, t_fd *fd)
{
	fd->infile = open(redir->directory, O_RDONLY);
	dup2(fd->infile, STDIN_FILENO);
	close(fd->infile);
}

static void	heredoc(t_proc *proc, t_fd *fd)
{
	int		buffer_fd;
	char	*buffer;

	fd->heredoc_exist = 1;
	buffer_fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(buffer_fd, STDOUT_FILENO);
	close(buffer_fd);
	while (1)
	{
		buffer = malloc(sizeof(char) * 1000);
		read(0, buffer, 1000);
		if (!ft_strncmp(buffer, proc->redir_in->directory,
				ft_strlen(proc->redir_in->directory)))
		{
			free(buffer);
			break ;
		}
		ft_putstr(buffer);
		free(buffer);
	}
	buffer_fd = open("/tmp/heredoc", O_RDONLY);
	dup2(buffer_fd, STDIN_FILENO);
	close(buffer_fd);
}

void	redirect_in(t_proc *proc, t_fd *fd)
{
	while (proc->redir_in)
	{
		if (proc->redir_in->flag == IN_TRUNC)
			in_trunc(proc->redir_in, fd);
		if (proc->redir_in->flag == IN_APPEND)
			heredoc(proc, fd);
		proc->redir_in = proc->redir_in->next;
	}
}
