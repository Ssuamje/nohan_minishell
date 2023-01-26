/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:36:30 by sanan             #+#    #+#             */
/*   Updated: 2023/01/26 15:48:31 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

t_list	*tokenize(char *input, t_lexer *lexer)
{
	int		idx;
	t_list	*token_list;

	idx = 0;
	token_list = ft_lstnew(NULL);
	while (input[idx] != '\0')
	{
		lexical_analyze(token_list, &input[idx], lexer);
		idx++;
	}
	if (lexer->status != LEX_NORMAL)
		put_token_to_list(lexer, token_list);
	return (token_list);
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

void	put_token_to_list(t_lexer *lexer, t_list *token_list)
{
	t_token	*token;
	// char	*tmp;

	token = get_token();
	token->status = lexer->status;
	token->string = get_processed_string(lexer);
	// tmp = token->string;
	// token->string = ft_strtrim(tmp, " \t");
	// free(tmp);
	ft_lstadd_back(&token_list, ft_lstnew(token));
}

//print_token need to be deleted
void	print_token(t_list *token_list)
{
	t_list	*tmp;
	t_token	*token;

	tmp = token_list->next;
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
		printf(" string : _%s_}\n\n", token->string);
		tmp = tmp->next;
	}
}

void	free_token_list(t_list **token_list)
{
	t_list	*tmp;

	tmp = *token_list;
	while (tmp)
	{
		*token_list = tmp->next;
		if (tmp->content)
			free(((t_token *)tmp->content)->string);
		ft_lstdelone(tmp, free);
		tmp = *token_list;
	}
}
