/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 20:57:16 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

static void	in_trunc(t_process *proc)
{
	proc->fd_infile = open(((t_redir *)proc->redir_in->content)->file, O_RDONLY);
	dup2(proc->fd_infile, STDIN_FILENO);
	close(proc->fd_infile);
}

// static void	heredoc(t_process *proc)
// {
// 	int			buffer_fd;
// 	char		*buffer;
// 	int			old_fd;
// 	size_t		buffer_len;

// 	old_fd = dup(STDOUT_FILENO);
// 	buffer_fd = open(proc->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	dup2(buffer_fd, STDOUT_FILENO);
// 	close(buffer_fd);
// 	while (1)
// 	{
// 		buffer = malloc(sizeof(char) * 1000);
// 		read(0, buffer, 1000);
// 		buffer_len = 0;
// 		while (buffer[buffer_len] != '\n')
// 			buffer_len++;
// 		if (!ft_strncmp(buffer, proc->redir_in->file,
// 				ft_strlen(proc->redir_in->file)) && buffer_len == ft_strlen(proc->redir_in->file))
// 		{
// 			free(buffer);
// 			break ;
// 		}
// 		ft_putstr(buffer);
// 		free(buffer);
// 	}
// 	dup2(old_fd, STDOUT_FILENO);
// 	buffer_fd = open(proc->heredoc, O_RDONLY);
// 	dup2(buffer_fd, STDIN_FILENO);
// 	close(buffer_fd);
// }

void	redirect_in(t_process *proc)
{
	if (proc->redir_in != NULL)
	{
		if (proc->redir_in->flag == IN_TRUNC)
			in_trunc(proc);
		// else if (proc->redir_in->flag == IN_APPEND)
		// 	heredoc(proc);
	}
}
