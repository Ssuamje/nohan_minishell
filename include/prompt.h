/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:38:04 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 22:02:16 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "error.h"
# include "readline/readline.h"
# include "parser.h"
# include "minishell.h"
# include "envl.h"
# include "utils.h"
# include "builtin.h"

int		get_len(char *str);
void	sighandler(int signo);
int		is_string_only_white_spaces(char *str);
int		is_input_empty(char *input);

#endif