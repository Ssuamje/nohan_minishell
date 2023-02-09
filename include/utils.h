/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:01:35 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 12:55:05 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parser.h"

typedef struct s_process	t_process;
typedef struct s_redir		t_redir;

int		is_in_str(char c, char *str);
int		is_cmd_has_special_after(char *cmd);

#endif