/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:41 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/04 13:06:46 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "libft.h"
# include "redirection.h"
# include "execute.h"
# include "parser.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define READ 0
# define WRITE 1

void	execute(t_process *cur_proc, t_process *next_proc, int pfd[], char **path, char **envp);
void	free_env_path(t_env *env);
void	env_path(t_env *env, char **envp);
void	exec_process(char **envp, t_list *processes);
void	pipe_process(t_list *processes, int *pfd, char **env_path, char **envp, int stdfd[]);
void	env_command(t_process *cur_proc, t_process *next_proc, int pfd[], char **path, char **envp);
#endif