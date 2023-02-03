/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:53:34 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/03 13:07:49 by hyungnoh         ###   ########.fr       */
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

typedef struct s_env
{
	char	**path;
}	t_env;

void	redirection(t_process *proc);
void	redirect_in(t_process *proc);
void	redirect_out(t_process *proc);
void	set_heredoc_fd(t_list *procs, int stdfd[]);

#endif