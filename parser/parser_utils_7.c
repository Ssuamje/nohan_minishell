/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:37:11 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:37:21 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	parse_init(t_token *token, t_parser *parser)
{
	parser->status = token->status;
	if (token->status == PAR_PIPE)
		return (ERR_TRUE);
	if (token->status == PAR_REDIRECT)
	{
		parser->flag_redir = get_redir_flag(token->string);
		return (ERR_FALSE);
	}
	ft_lstadd_back(&(parser->argv), ft_lstnew(ft_strdup(token->string)));
	return (ERR_FALSE);
}
