/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:52:41 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/04 18:58:06 by sanan            ###   ########.fr       */
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

# define CHILD 0
# define PARENTS 1

void	execute(t_process *cur, t_process *next, t_info *info, char **envp);

#endif