/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:36:30 by sanan             #+#    #+#             */
/*   Updated: 2023/01/29 21:38:32 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

t_list	*tokenize(char *input, t_lexer *lexer)
{
	int		idx;
	t_list	*tokens;

	idx = 0;
	tokens = ft_lstnew(NULL);
	while (input[idx] != '\0')
	{
		lexical_analyze(tokens, &input[idx], lexer);
		idx++;
	}
	if (lexer->status != LEX_NORMAL)
		put_token_to_list(lexer, tokens);
	return (tokens);
}

t_token	*get_token(void)
{
	t_token	*to_return;

	to_return = malloc(sizeof(t_token));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->status = LEX_NORMAL;
	to_return->string = NULL;
	return (to_return);
}

void	put_token_to_list(t_lexer *lexer, t_list *tokens)
{
	t_token	*token;

	token = get_token();
	token->status = lexer->status;
	token->is_seperated = FALSE;
	token->string = get_processed_string(lexer);
	ft_lstadd_back(&tokens, ft_lstnew(token));
}

//print_token need to be deleted
void	print_token(t_list *tokens)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens->next;
	while (tmp != NULL)
	{
		token = tmp->content;
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
		tmp = tmp->next;
	}
}

void	free_tokens(t_list **tokens)
{
	t_list	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		*tokens = tmp->next;
		if (tmp->content)
			free(((t_token *)tmp->content)->string);
		ft_lstdelone(tmp, free);
		tmp = *tokens;
	}
}
