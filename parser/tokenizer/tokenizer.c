/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:36:30 by sanan             #+#    #+#             */
/*   Updated: 2023/02/07 15:00:33 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"
#include "../../include/parser.h" // delete

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

void	free_tokens(t_list **tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;

	tmp = (*tokens)->next;
	while (tmp)
	{
		tmp_token = tmp->content;
		if (tmp_token->string)
			free(tmp_token->string);
		tmp = tmp->next;
	}
	ft_lstclear(tokens, free);
	free(*tokens);
}

void	free_double(void *p1, void *p2)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
}
