/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:15:56 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 20:15:41 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	quotation_status(t_list *tokens, char *c, t_lexer *lexer)
{
	int	cur_status;

	cur_status = get_status(*c);
	if (lexer->quote_flag == TRUE)
	{
		add_char_to_buffer(get_char(c), lexer);
		return ;
	}
	else if (cur_status == LEX_QUOTATION)
	{
		add_char_to_buffer(get_char(c), lexer);
		put_token_to_list(lexer, tokens);
		lexer->status = LEX_NORMAL;
		return ;
	}
	put_token_to_list(lexer, tokens);
	add_char_to_buffer(get_char(c), lexer);
	lexer->status = cur_status;
}

void	apostrophe_status(t_list *tokens, char *c, t_lexer *lexer)
{
	int	cur_status;

	cur_status = get_status(*c);
	if (lexer->apost_flag == TRUE)
	{
		add_char_to_buffer(get_char(c), lexer);
		return ;
	}
	else if (cur_status == LEX_APOSTROPHE)
	{
		add_char_to_buffer(get_char(c), lexer);
		put_token_to_list(lexer, tokens);
		lexer->status = LEX_NORMAL;
		return ;
	}
	put_token_to_list(lexer, tokens);
	add_char_to_buffer(get_char(c), lexer);
	lexer->status = cur_status;
}

void	pipe_status(t_list *tokens, char *c, t_lexer *lexer)
{
	int	cur_status;

	cur_status = get_status(*c);
	if (cur_status == LEX_PIPE)
	{
		add_char_to_buffer(get_char(c), lexer);
		return ;
	}
	put_token_to_list(lexer, tokens);
	add_char_to_buffer(get_char(c), lexer);
	lexer->status = cur_status;
	return ;
}

void	env_status(t_list *tokens, char *c, t_lexer *lexer)
{
	int	cur_status;

	cur_status = get_status(*c);
	if ((*c != ':') && (cur_status == LEX_STRING \
		|| cur_status == LEX_ENV))
		add_char_to_buffer(get_char(c), lexer);
	else
	{
		put_token_to_list(lexer, tokens);
		ft_lstadd_back(&(lexer->str_buffer), ft_lstnew(get_char(c)));
		if (lexer->apost_flag == TRUE)
			lexer->status = LEX_APOSTROPHE;
		else if (lexer->quote_flag == TRUE)
			lexer->status = LEX_QUOTATION;
		else
			lexer->status = cur_status;
	}
}

void	lexical_analyze(t_list *tokens, char *c, t_lexer *lexer)
{
	check_apost_quote_flag(c, lexer);
	if (lexer->status == LEX_NORMAL)
		return (normal_status(tokens, c, lexer));
	if (lexer->status == LEX_STRING)
		return (string_status(tokens, c, lexer));
	if (lexer->status == LEX_REDIRECT)
		return (redirect_status(tokens, c, lexer));
	if (lexer->status == LEX_QUOTATION)
		return (quotation_status(tokens, c, lexer));
	if (lexer->status == LEX_APOSTROPHE)
		return (apostrophe_status(tokens, c, lexer));
	if (lexer->status == LEX_PIPE)
		return (pipe_status(tokens, c, lexer));
	if (lexer->status == LEX_ENV)
		return (env_status(tokens, c, lexer));
}
