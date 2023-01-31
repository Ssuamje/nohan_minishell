/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 21:05:10 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

static void	in_trunc(t_process *proc, t_redir *redir)
{
	proc->fd_infile = open(redir->file, O_RDONLY);
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
	t_list	*tmp;
	t_redir *tmp_redir;

	tmp = proc->redir_in->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		tmp_redir = tmp->content;
		if (tmp_redir->flag == IN_TRUNC)
			in_trunc(proc, tmp_redir);
		tmp = tmp->next;
	}
}
