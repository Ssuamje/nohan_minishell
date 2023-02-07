/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:53:34 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/07 17:30:42 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "parser.h"
# include <sys/stat.h>

# define OPEN_ERROR -1

typedef struct s_process	t_process;

enum e_flag_redir{
	IN_TRUNC,
	IN_APPEND,
	OUT_TRUNC,
	OUT_APPEND,
};

typedef struct s_redir{
	int				flag;
	char			*file;
}	t_redir;

typedef struct s_info
{
	char	**path;
	int		process_cnt;
	int		stdfd[2];
}	t_info;

void	redirection(t_process *proc);
void	redirect_in(t_process *proc);
void	redirect_out(t_process *proc);
void	set_heredoc_fd(t_list *procs);
int		interpret_buffer_env(char **buffer);
void	interpret_redir_file(t_redir *redir);

#endif