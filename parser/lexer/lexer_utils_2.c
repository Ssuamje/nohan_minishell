/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 21:46:29 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 20:15:51 by sanan            ###   ########.fr       */
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

void	normal_status(t_list *tokens, char *c, t_lexer *lexer)
{
	int	cur_status;

	(void)tokens;
	cur_status = get_status(*c);
	if (cur_status == LEX_NORMAL
		&& (get_status(*(c + 1)) == LEX_STRING \
		|| get_status(*(c + 1)) == LEX_APOSTROPHE \
		|| get_status(*(c + 1)) == LEX_QUOTATION))
		return (add_char_to_buffer(get_char(c), lexer));
	if (*c == ' ' || *c == '\t')
		return ;
	lexer->status = cur_status;
	add_char_to_buffer(get_char(c), lexer);
}

void	string_status(t_list *tokens, char *c, t_lexer *lexer)
{
	int	cur_status;

	cur_status = get_status(*c);
	if (cur_status == LEX_STRING
		|| cur_status == LEX_ENV)
	{
		add_char_to_buffer(get_char(c), lexer);
		return ;
	}
	put_token_to_list(lexer, tokens);
	add_char_to_buffer(get_char(c), lexer);
	lexer->status = cur_status;
}

void	redirect_status(t_list *tokens, char *c, t_lexer *lexer)
{
	int	cur_status;

	cur_status = get_status(*c);
	if (cur_status != LEX_REDIRECT)
	{
		put_token_to_list(lexer, tokens);
		lexer->status = cur_status;
		add_char_to_buffer(get_char(c), lexer);
		return ;
	}
	add_char_to_buffer(get_char(c), lexer);
	lexer->status = cur_status;
}
