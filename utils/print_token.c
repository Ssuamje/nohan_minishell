/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:01:12 by sanan             #+#    #+#             */
/*   Updated: 2023/02/07 14:55:58 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	print_token(t_token *token)
{
	if (token->status == LEX_STRING)
		printf("{status : STRING,\n");
	if (token->status == LEX_NORMAL)
		printf("{status : NORMAL,\n");
	if (token->status == LEX_APOSTROPHE)
		printf("{status : APOSTROPHE,\n");
	if (token->status == LEX_ENV)
		printf("{status : ENV,\n");
	if (token->status == LEX_PIPE)
		printf("{status : PIPE,\n");
	if (token->status == LEX_QUOTATION)
		printf("{status : QUOTATION,\n");
	if (token->status == LEX_REDIRECT)
		printf("{status : REDIRECT,\n");
	if (token->is_seperated == TRUE)
		printf(" is_seperated = TRUE,\n");
	else
		printf(" is_seperated = FALSE,\n");
	printf(" string : _%s_}\n\n", token->string);
}

void	print_token_list(t_list *tokens)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens->next;
	while (tmp != NULL)
	{
		token = tmp->content;
		print_token(token);
		tmp = tmp->next;
	}
}
