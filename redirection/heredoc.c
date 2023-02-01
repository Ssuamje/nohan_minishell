/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:46:30 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/01 15:53:07 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"

static void	exec_heredoc(t_redir *redir, int pfd[])
{
	int			buffer_fd;
	char		*buffer;
	size_t		buffer_len;
	static int	idx;
	char		heredoc[2];
	pid_t		pid;
	int			status = -1;

	idx++;
	heredoc[0] = idx + 48;
	heredoc[1] = '\0';
	buffer_fd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		close(pfd[1]);
		dup2(buffer_fd, STDOUT_FILENO);
		close(buffer_fd);
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
	}
	else
	{
		close(pfd[1]);
		buffer_fd = open(heredoc, O_RDONLY, 0644);
		dup2(pfd[0], buffer_fd);
		close(buffer_fd);
		close(pfd[0]);
		wait(&status);
	}
}

void	heredoc(t_process *proc, int pfd[])
{
	t_list	*tmp;
	t_redir *tmp_redir;

	tmp = proc->redir_in->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		tmp_redir = tmp->content;
		if (tmp_redir->flag == IN_APPEND)
			exec_heredoc(tmp_redir, pfd);
		tmp = tmp->next;
	}
}
