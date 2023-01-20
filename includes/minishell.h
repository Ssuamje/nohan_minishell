/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:35:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/20 14:02:10 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "libft.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define READ 0
# define WRITE 1

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

void	env_path(char **path);

#endif