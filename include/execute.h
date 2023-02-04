/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:41 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/04 18:54:09 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include "redirection.h"
# include "libft.h"
# include "redirection.h"
# include "execute.h"
# include "parser.h"
# include "builtin.h"
# include "envl.h"
# include "minishell.h"

# define CHILD 0
# define PARENTS 1

void	execute(t_process *cur, t_process *next, t_info *info, char **envp);

void	free_env_path(t_env *env);
void	env_path(t_env *env, char **envp);
void	exec_process(char **envp, t_list *processes);
void	pipe_process(t_list *processes, int *pfd, char **env_path, char **envp, int stdfd[]);
void	env_command(t_process *cur_proc, t_process *next_proc, int pfd[], char **path, char **envp);
#endif