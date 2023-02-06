/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:38:04 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 18:13:58 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "error.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "parser.h"
# include "envl.h"
# include "execute.h"
# include "utils.h"
# include "builtin.h"

int		get_len(char *str);
void	sighandler(int signo);
int		is_string_only_white_spaces(char *str);
int		is_input_empty(char *input);
void	init_sighandler(void);
void	set_sigint_to_default(void);
void	print_logo(void);

#endif
