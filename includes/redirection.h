/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:53:34 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 17:41:13 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

enum e_flag_redir{
	IN_TRUNC,
	IN_APPEND,
	OUT_TRUNC,
	OUT_APPEND,
};

typedef struct s_redir{
	int				flag;
	char			*directory;
}	t_redir;

typedef struct s_proc{
	t_redir			*redir_in;
	t_redir			*redir_out;
	char			**command;
	int				infile;
	int				outfile;
	char			*heredoc;
	struct s_proc	*next;
}	t_proc;

typedef struct s_env
{
	char	**path;
}	t_env;

void	redirect_in(t_proc *proc);
void	redirect_out(t_proc *proc);

#endif