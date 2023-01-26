/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:53:34 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/26 22:38:47 by hyungseok        ###   ########.fr       */
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
	struct s_redir	*next;
}	t_redir;

typedef struct s_proc{
	t_redir			*redir_in;
	t_redir			*redir_out;
	char			**command;
	struct s_proc	*next;
}	t_proc;

typedef struct s_fd
{
	int		infile;
	int		outfile;
}	t_fd;

typedef struct s_env
{
	char	**path;
}	t_env;

void	redirect_in(t_proc *proc, t_fd *fd);
void	redirect_out(t_proc *proc, t_fd *fd);

#endif