/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/01/30 14:18:39 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
# define ERR_TRUE 0
# define ERR_FALSE 1

t_process	*get_process(void)
{
	t_process	*to_return;

	to_return = malloc(sizeof(t_process));
		exit_error(ERR_MALLOC);
	to_return->cmd = NULL;
	to_return->redir_in = NULL;
	to_return->redir_out = NULL;
	return (to_return);
}

t_parser	*get_parser(void)
{
	t_parser	*to_return;

	to_return = malloc(sizeof(t_parser));
		exit_error(ERR_MALLOC);
	to_return->status = FALSE;
	to_return->arg = NULL;
	to_return->cmd = NULL;
	return (to_return);
}

// void	parse_tokens(t_list *tokens, t_list *processes)
// {
// 	t_list	*cursor;
// 	t_token	*tmp_token;

// 	cursor = tokens->next;
// 	while (cursor != NULL)
// 	{
// 		tmp_token = cursor->content;
// 		if (tmp_token->status == PAR_PIPE)

// 		if (tmp_token->status == PAR_REDIRECT)
// 			parse_redir(tmp_token, processes);
// 	}
// }

int	syntax_string(t_token *cur)
{
	(void)cur;
	return (ERR_FALSE);
}

int	syntax_redirect(t_token *cur)
{
	return (ft_strcmp(cur->string, "<")
		||	ft_strcmp(cur->string, "<<")
		||	ft_strcmp(cur->string, ">")
		||	ft_strcmp(cur->string, ">>"));
}

int	syntax_quotes(t_token *cur)
{
	if (cur->status == PAR_QUOTATION)
		return ((count_char(cur->string, '\"') % 2) == 0);
	if (cur->status == PAR_APOSTROPHE)
		return ((count_char(cur->string, '\'') % 2) == 0);
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

int	check_syntax(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;
	int		err;

	tmp = tokens->next;
	while (tmp != NULL)
	{
		tmp_token = tmp->content;
		printf("status = %d, string = %s\n", tmp_token->status, tmp_token->string);
		if (tmp_token->status == PAR_STRING)
			err = syntax_string(tmp_token);
		if (tmp_token->status == PAR_REDIRECT)
			err = syntax_redirect(tmp_token);
		if (tmp_token->status == PAR_QUOTATION
		||	tmp_token->status == PAR_APOSTROPHE)
			err = syntax_quotes(tmp_token);
		if (tmp_token->status == PAR_PIPE)
			err = syntax_pipe(tmp_token);
		if (tmp_token->status == PAR_ENV)
			err = syntax_env(tmp_token);
		if (err == ERR_TRUE)
			return (ERR_TRUE);
		tmp = tmp->next;
	}
	return (TRUE);
}

t_list *parse(char **envp, char *input)
{
	t_list		*tokens;
	// t_list		*processes;
	// t_parser	*parser;

	tokens = get_processed_tokens(envp, input);
	if (tokens == NULL)
	{
		free_tokens(&tokens);
		printf("invalid env!\n");
		return (NULL);
	}
	print_token(tokens);
	// parser = get_parser();
	if (check_syntax(tokens) == ERR_TRUE)
	{
		printf("syntax error occurred!\n");
		return (NULL);
	}
	// parse_tokens(tokens, processes);
	// free_tokens(&tokens);
	return (tokens);
}

//해당 토큰에 따라 상태를 갖는다.
//seperated 플래그를 통해 붙일지 말지를 정한다.