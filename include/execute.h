/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:41 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 13:46:18 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdio.h>
# include <sys/stat.h>
# include "redirection.h"
# include "libft.h"
# include "parser.h"
# include "builtin.h"
# include "envl.h"
# include "minishell.h"

# define RELATVIE 0
# define ABSOLUTE 1
# define CHILD 0
# define PARENTS 1

void	execute(t_process *cur, t_process *next, t_info *info, char **envp);
char	*find_full_path(t_process *cur, char **path, int *flag);
int		check_cmd(t_process *cur, char **path);
void	manage_pipe(t_process *cur, t_process *next, char **path, pid_t pid);
int		find_last_slash_index(char *cmd);
void	parse_cmd(t_process *cur);

#endif