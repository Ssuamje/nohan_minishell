/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/01/30 19:32:09 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

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

int	check_first_arg(t_token *token)
{
	return (token->status != LEX_PIPE);
}

int	get_redir_flag(char *redir)
{
	if (ft_strcmp(redir, "<") == TRUE)
		return (REDIR_L);
	if (ft_strcmp(redir, "<<") == TRUE)
		return (REDIR_LL);
	if (ft_strcmp(redir, ">") == TRUE)
		return (REDIR_R);
	if (ft_strcmp(redir, ">>") == TRUE)
		return (REDIR_RR);
	return (FALSE);
}

void	free_parser(t_parser **parser)
{
	free((*parser)->argv);
	if ((*parser)->string)
		free((*parser)->string);
	free(*parser);
}

int	check_syntax(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;
	int		err;

	tmp = tokens->next;
	if (check_first_arg(tokens->next->content) == ERR_TRUE)
		return (ERR_TRUE);
	while (tmp != NULL)
	{
		tmp_token = tmp->content;
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

t_process	*get_process(void)
{
	t_process	*to_return;

	to_return = malloc(sizeof(t_process));
	if (to_return == NULL)
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
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->status = FALSE;
	to_return->flag_redir = FALSE;
	to_return->string = NULL;
	to_return->argv = ft_lstnew(NULL);
	return (to_return);
}

void	parse_init(t_token *token, t_parser *parser)
{
	if (token->status == PAR_REDIRECT)
	{
		parser->status = PAR_REDIRECT;
		parser->flag_redir = get_redir_flag(token->string);
		return ;
	}
	parser->status = token->status;
	ft_lstadd_back(&parser->argv, ft_lstnew(ft_strdup(token->string)));
}

// void	process_redir_token(t_token *token, t_parser *parser, t_process *proc)
// {
// 	parse_token_to_redir(parser, proc);
// 	parser->status = PAR_REDIRECT;
// 	parser->flag_redir = get_redir_flag(token->string);
// }


// int	parse_tokens(t_list *tokens, t_list *processes, t_parser *parser)
// {
// 	t_list		*tmp;
// 	t_token		*tmp_token;

// 	tmp = tokens->next;
// 	while (tmp != NULL)
// 	{
// 		tmp_token = tmp->content;
// 		tmp = tmp->next;
// 	}
// }

int		check_join_condition(t_token *next_token)
{
	return (next_token->is_seperated == FALSE
		&&	(next_token->status == PAR_STRING ||
			next_token->status == PAR_QUOTATION ||
			next_token->status == PAR_APOSTROPHE ||
			next_token->status == PAR_ENV));
}

void	join_tokens(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;
	t_token	*next_token;

	tmp = tokens->next;
	while (tmp->next != NULL
	&&	tmp->next->content != NULL)
	{
		tmp_token = tmp->content;
		if (tmp_token->status == PAR_REDIRECT
		||	tmp_token->status == PAR_PIPE)
		{
			tmp = tmp->next;
			continue ;
		}
		next_token = tmp->next->content;
		if (check_join_condition(next_token) != FALSE)
		{
			tmp_token->string = ft_join_and_free(tmp_token->string, next_token->string);
			tmp = ft_lstpop(tokens, tmp->next, LST_LEFT);
			continue ;
		}
		tmp = tmp->next;
	}
}


t_list *parse(char **envp, char *input)
{
	t_list		*tokens;
	t_list		*processes;
	t_parser	*parser;

	tokens = get_processed_tokens(envp, input);
	if (tokens == NULL)
	{
		free_tokens(&tokens);
		printf("invalid env!\n");
		return (NULL);
	}
	// print_token(tokens);
	if (check_syntax(tokens) == ERR_TRUE)
	{
		printf("syntax error occurred!\n");
		return (NULL);
	}
	parser = get_parser();
	processes = ft_lstnew(NULL);
	join_tokens(tokens);
	print_token(tokens);
	// if (parse_tokens(tokens, processes, parser) == ERR_TRUE)
	// {
	// 	printf("parse error occurred!\n");
	// 	return (NULL);
	// }
	free_tokens(&tokens);
	free_parser(&parser);
	return (processes);
}

//해당 토큰에 따라 상태를 갖는다.
//seperated 플래그를 통해 붙일지 말지를 정한다.