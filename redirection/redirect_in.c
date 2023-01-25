/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/25 21:57:08 by hyungseok        ###   ########.fr       */
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
	char	*pile;

	pile = NULL;
	buffer_fd = open("heredoc_buffer", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(buffer_fd, STDOUT_FILENO);
	close(buffer_fd);
	while (1)
	{
		buffer = malloc(sizeof(char) * 100);
		for (size_t i = 0; i < 100; i++)
			buffer[i] = '\0';
		read(0, buffer, 99);
		if (!ft_strncmp(buffer, proc->redir_in->directory, ft_strlen(proc->redir_in->directory)))
		{
			free(buffer);
			break ;
		}
		if (pile == NULL)
			pile = ft_strdup(buffer);
		else
			pile = ft_strjoin(pile, buffer);
		free(buffer);
	}
	ft_putstr(pile);
	free(pile);
	// if (!ft_strncmp("cat", proc->command[0], 3) && proc->command[1] == NULL)
	// 	proc->command[1] = "heredoc_buffer";
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
