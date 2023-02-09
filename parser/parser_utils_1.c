/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:37:34 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 10:58:55 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	syntax_string(t_token *cur)
{
	if (ft_strcmp(cur->string, "(") == TRUE \
	|| ft_strcmp(cur->string, ")") == TRUE)
		return (ERR_TRUE);
	return (ERR_FALSE);
}

int	syntax_redirect(t_token *cur)
{
	return (ft_strcmp(cur->string, "<") \
		|| ft_strcmp(cur->string, "<<") \
		|| ft_strcmp(cur->string, ">") \
		|| ft_strcmp(cur->string, ">>"));
}

int	syntax_quotes(t_token *cur)
{
	if (cur->status == PAR_QUOTATION)
		return (count_char(cur->string, '\"') == 0);
	if (cur->status == PAR_APOSTROPHE)
		return (count_char(cur->string, '\'') == 0);
	return (ERR_TRUE);
}

int	syntax_pipe(t_token *cur)
{
	return (ft_strcmp(cur->string, "|"));
}

int	syntax_env(t_token *cur)
{
	(void)cur;
	return (ERR_FALSE);
}
