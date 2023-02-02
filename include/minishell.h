/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:35:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/03 01:08:40 by hyungseok        ###   ########.fr       */
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
# include "parser.h"

t_list *g_envl;

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define READ 0
# define WRITE 1

void	env_path(t_env *env, char **envp);
void	free_env_path(t_env *env);
void	exec_process(char **envp, t_list *processes);

#endif