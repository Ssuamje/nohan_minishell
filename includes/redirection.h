/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:53:34 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/30 18:59:30 by hyungseok        ###   ########.fr       */
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
	int				infile;
	int				outfile;
	int				pip[2];
	int				outfile_exist;
	struct s_proc	*prev;
	struct s_proc	*next;
}	t_proc;

typedef struct s_env
{
	char	**path;
}	t_env;

void	redirect_in(t_proc *proc);
void	redirect_out(t_proc *proc);

#endif