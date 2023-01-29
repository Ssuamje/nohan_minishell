/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:20:29 by sanan             #+#    #+#             */
/*   Updated: 2023/01/29 21:33:07 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "tokenizer.h"

enum e_parser_status{
	PAR_STRING = 1,
	PAR_REDIRECT,
	PAR_QUOTATION,
	PAR_APOSTROPHE,
	PAR_PIPE,
	PAR_ENV,
};

typedef struct s_process{
	t_list	*redir_in;
	t_list	*redir_out;
	char	**cmd;
}	t_process;

t_list *parse(char **envp, char *input);

#endif