/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:35:03 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/01 14:07:42 by sanan            ###   ########.fr       */
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
void	exec_process(char **envp, t_list *processes);

#endif