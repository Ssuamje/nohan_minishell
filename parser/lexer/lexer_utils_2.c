/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 21:46:29 by sanan             #+#    #+#             */
/*   Updated: 2023/01/24 15:34:44 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

char	*get_char(char *ptr)
{
	char	*to_return;

	to_return = malloc(sizeof(char));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	*to_return = *ptr;
	return (to_return);
}

int	get_status(char c)
{
	if (c == ' ' || c == '\t')
		return (LEX_NORMAL);
	else if (c == '\"')
		return (LEX_QUOTATION);
	else if (c == '\'')
		return (LEX_APOSTROPHE);
	else if (c == '<' || c == '>')
		return (LEX_REDIRECT);
	else if (c == '|')
		return (LEX_PIPE);
	else if (c == '$')
		return (LEX_ENV);
	else
		return (LEX_STRING);
}

int	normal_status(t_list *token_list, char *c, t_lexer *lexer)
{
	int	cur_status;

	(void)token_list;
	if (*c == ' ' || *c == '\t')
		return (FALSE);
	cur_status = get_status(*c);
	lexer->status = cur_status;
	add_char_to_buffer(get_char(c), lexer);
	return (TRUE);
}

int	string_status(t_list *token_list, char *c, t_lexer *lexer)
{
	int	cur_status;

	cur_status = get_status(*c);
	if (cur_status != LEX_STRING)
	{
		put_token_to_list(lexer, token_list);
		lexer->status = cur_status;
		add_char_to_buffer(get_char(c), lexer);
		return (TRUE);
	}
	add_char_to_buffer(get_char(c), lexer);
	lexer->status = cur_status;
	return (TRUE);
}

int	redirect_status(t_list *token_list, char *c, t_lexer *lexer)
{
	int	cur_status;

	cur_status = get_status(*c);
	if (cur_status != LEX_REDIRECT)
	{
		put_token_to_list(lexer, token_list);
		lexer->status = cur_status;
		add_char_to_buffer(get_char(c), lexer);
		return (TRUE);
	}
	add_char_to_buffer(get_char(c), lexer);
	lexer->status = cur_status;
	return (TRUE);
}
