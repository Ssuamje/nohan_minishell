/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:01:35 by sanan             #+#    #+#             */
/*   Updated: 2023/02/04 22:56:49 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parser.h"

typedef struct s_process	t_process;
typedef struct s_redir		t_redir;

void	print_token(t_token *token);
void	print_token_list(t_list *tokens);
void	print_process(t_process *proc, int idx);
void	print_processes_list(t_list *processes);
void	print_split(char **split);
void	print_redir(t_redir *redir);
void	print_redir_list(t_list *redir_list);
int		is_in_str(char c, char *str);
int		is_cmd_has_special_after(char *cmd);

#endif