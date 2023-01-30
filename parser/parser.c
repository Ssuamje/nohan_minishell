/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/01/30 19:04:19 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
# define ERR_TRUE 0
# define ERR_FALSE 1
# define LST_LEFT 0
# define LST_RIGHT 1

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

// void	parse_token_to_process(t_parser *parser, t_list *processes)
// {
	
// }


t_redir	*get_redir_token(t_parser *parser)
{
	t_redir	*to_return;

	to_return = malloc(sizeof(t_redir));
	to_return->flag = parser->flag_redir;
	to_return->file = ft_strdup(parser->string);
	free(parser->string);
	return (to_return);
}

void	parse_token_to_redir(t_parser *parser, t_process *proc)
{
	if (parser->flag_redir == REDIR_L
	||	parser->flag_redir == REDIR_LL)
		ft_lstadd_back(&proc->redir_in, ft_lstnew(get_redir_token(parser)));
	if (parser->flag_redir == REDIR_R
	||	parser->flag_redir == REDIR_RR)
		ft_lstadd_back(&proc->redir_out, ft_lstnew(get_redir_token(parser)));
}

void	process_redir_token(t_token *token, t_parser *parser, t_process *proc)
{
	parse_token_to_redir(parser, proc);
	parser->status = PAR_REDIRECT;
	parser->flag_redir = get_redir_flag(token->string);
}

void	parse_string(t_token *token, t_parser *parser, t_process *proc)
{
	if (parser->flag_redir != FALSE)
	{
		process_redir_token(token, parser, proc);
		return ;
	}
	if (token->is_seperated == FALSE)
		parser->string = ft_join_and_free(token->string, parser->string);
	else
	{
		ft_lstadd_back(&parser->argv, ft_lstnew(ft_strdup(token->string)));
		parser->status = token->status;
	}
}

void	parse_quotes(t_token *token, t_parser *parser, t_process *proc)
{
	if (token->status == PAR_REDIRECT)
	{
		process_redir_token(token, parser, proc);
		return ;
	}
	if (token->is_seperated == FALSE)
		parser->string = ft_join_and_free(token->string, parser->string);
	else
		ft_lstadd_back(&parser->argv, ft_lstnew(ft_strdup(token->string)));
	parser->status = token->status;
}

// void	parse_redirect(t_token *token, t_parser *parser, t_process *proc)
// {
// 	if (parser->flag_redir != FALSE)
	
// }

void	parse_tokens(t_list *tokens, t_list *processes, t_parser *parser)
{
	t_list		*tmp;
	t_token		*tmp_token;
	t_process	*cur_proc;

	tmp = tokens->next;
	cur_proc = processes->next->content;
	(void)cur_proc;
	(void)tmp_token;
	(void)parser;
	while (tmp != NULL)
	{
		// tmp_token = tmp->content;
		// if (tmp_token->status == PAR_PIPE)
		// {
		// 	parse_token_to_process(parser, processes);
		// 	continue ;
		// }
		// if (parser->status == FALSE)
		// 	parse_init(tmp_token, parser);
		// else if (parser->status == PAR_STRING)
		// 	parse_string(tmp_token, parser, cur_proc);
		// else if (parser->status == PAR_REDIRECT)
		// 	parse_redirect(tmp_token, parser, cur_proc);
		// else if (parser->status == PAR_QUOTATION
		// ||	parser->status == PAR_APOSTROPHE)
		// 	parse_quotes(tmp_token, parser, cur_proc);
		// else if (parser->status == PAR_ENV)
		// 	parse_env(tmp_token, parser, cur_proc);
		tmp = tmp->next;
	}
}

void	join_tokens(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;
	t_token	*next_token;
	char	*tmp_str;

	tmp = tokens->next;
	while (tmp->next != NULL && tmp->next->content != NULL)
	{
		tmp_token = tmp->content;
		next_token = tmp->next->content;
		if (next_token->is_seperated == FALSE
		&&	(next_token->status == PAR_STRING ||
			next_token->status == PAR_QUOTATION ||
			next_token->status == PAR_APOSTROPHE ||
			next_token->status == PAR_ENV))
		{
			tmp_str = tmp_token->string;
			tmp_token->string = ft_join_and_free(tmp_str, next_token->string);
			tmp = ft_lstpop(tokens, tmp->next, LST_LEFT);
			continue ;
		}
		tmp = tmp->next;
	}
}

void	free_parser(t_parser **parser)
{
	free((*parser)->argv);
	if ((*parser)->string)
		free((*parser)->string);
	free(*parser);
}

t_list *parse(char **envp, char *input)
{
	t_list		*tokens;
	// t_list		*processes;
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
	// processes = ft_lstnew(NULL);
	join_tokens(tokens);
	print_token(tokens);
	// parse_tokens(tokens, processes, parser);
	free_tokens(&tokens);
	free_parser(&parser);
	return (NULL);
}

//해당 토큰에 따라 상태를 갖는다.
//seperated 플래그를 통해 붙일지 말지를 정한다.