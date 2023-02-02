/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:01:35 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 14:22:16 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "parser.h"

typedef struct s_process t_process;
typedef struct s_redir t_redir;

void	print_token(t_token *token);
void	print_token_list(t_list *tokens);
void	print_process(t_process *proc, int idx);
void	print_processes_list(t_list *processes);
void	print_split(char **split);
void	print_envl(t_list *envl);
void	print_redir(t_redir *redir);
void	print_redir_list(t_list *redir_list);

#endif