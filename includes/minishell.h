/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:35:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 16:38:50 by hyungnoh         ###   ########.fr       */
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
# include "redirection.h"
# include "execute.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define READ 0
# define WRITE 1

void	env_path(t_env *env, char **envp);
int		get_child_size(t_proc *proc);

#endif