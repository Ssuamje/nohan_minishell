/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 14:26:28 by hyungnoh         ###   ########.fr       */
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

int	is_token_not_env_not_has_special(t_token *token)
{
	return (is_in_charset(token->string[0], "~!@#$%^&*()_+`-=[]{}\\|/?><,.")
		&&	(token->status != PAR_ENV));
}

int	check_first_arg(t_token *token)
{
	return (token->status != PAR_PIPE
		&&	token->status != PAR_REDIRECT
		&&	is_token_not_env_not_has_special(token) == FALSE);
}

int	get_redir_flag(char *redir)
{
	if (ft_strcmp(redir, "<") == TRUE)
		return (IN_TRUNC);
	if (ft_strcmp(redir, "<<") == TRUE)
		return (IN_APPEND);
	if (ft_strcmp(redir, ">") == TRUE)
		return (OUT_TRUNC);
	if (ft_strcmp(redir, ">>") == TRUE)
		return (OUT_APPEND);
	return (FALSE);
}

void	free_parser(t_parser **parser)
{
	ft_lstclear(&((*parser)->argv), free);
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
	to_return->redir_in = ft_lstnew(NULL);
	to_return->redir_out = ft_lstnew(NULL);
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
			tmp_token->string = ft_join_and_free(tmp_token->string, \
												next_token->string);
			tmp = ft_lstpop(tokens, tmp->next, LST_LEFT);
			continue ;
		}
		tmp = tmp->next;
	}
}

int	parse_init(t_token *token, t_parser *parser)
{
	parser->status = token->status;
	if (token->status == PAR_PIPE)
		return (ERR_TRUE);
	if (token->status == PAR_REDIRECT)
	{
		parser->flag_redir = get_redir_flag(token->string);
		return (ERR_FALSE);
	}
	ft_lstadd_back(&(parser->argv), ft_lstnew(ft_strdup(token->string)));
	return (ERR_FALSE);
}


t_redir	*get_redir(t_parser *parser)
{
	t_redir *to_return;

	to_return = malloc(sizeof(t_redir));
	to_return->flag = parser->flag_redir;
	to_return->file = ft_strdup(parser->string);
	return (to_return);
}

void	put_redir_token(t_parser *parser, t_process *cur_proc)
{
	if (parser->flag_redir == IN_TRUNC
	||	parser->flag_redir == IN_APPEND)
		ft_lstadd_back(&(cur_proc->redir_in), ft_lstnew(get_redir(parser)));
	if (parser->flag_redir == OUT_TRUNC
	||	parser->flag_redir == OUT_APPEND)
		ft_lstadd_back(&(cur_proc->redir_out), ft_lstnew(get_redir(parser)));
}

int	parse_string(t_token *token, t_parser *parser)
{
	parser->status = token->status;
	if (token->status == PAR_REDIRECT)
	{
		parser->flag_redir = get_redir_flag(token->string);
		parser->status = PAR_REDIRECT;
		return (ERR_FALSE);
	}
	ft_lstadd_back(&(parser->argv), ft_lstnew(ft_strdup(token->string)));
	return (ERR_FALSE);
}

int	parse_redirect(t_token *token, t_parser *parser, t_process *cur_proc)
{
	parser->status = token->status;
	if (token->status == PAR_REDIRECT
	||	token->status == PAR_PIPE)
		return (ERR_TRUE);
	parser->string = ft_strdup(token->string);
	put_redir_token(parser, cur_proc);
	return (ERR_FALSE);
}

void	argv_list_to_split(t_process *cur_proc, t_parser *parser)
{
	char	**split;
	int		count_nodes;
	t_list	*cmd_list;
	int		idx;

	cmd_list = parser->argv->next;
	count_nodes = ft_lstsize(cmd_list);
	split = malloc(sizeof(char *) * (count_nodes + 1));
	split[count_nodes] = NULL;
	idx = 0;
	while (idx < count_nodes && cmd_list != NULL)
	{
		split[idx] = ft_strdup(cmd_list->content);
		idx++;
		cmd_list = cmd_list->next;
	}
	cur_proc->cmd = split;
	ft_lstclear(&(parser->argv), free);
	ft_lstadd_back(&(parser->argv), ft_lstnew(NULL));
}

int	parse_tokens(t_list *tokens, t_list *processes, t_parser *parser)
{
	t_list		*tmp;
	t_token		*tmp_token;
	t_process	*cur_proc;
	int		err;

	tmp = tokens->next;
	cur_proc = get_process();
	err = ERR_FALSE;
	while (tmp != NULL)
	{
		tmp_token = tmp->content;
		if (tmp_token->status == PAR_PIPE)
		{
			argv_list_to_split(cur_proc, parser);
			ft_lstadd_back(&processes, ft_lstnew(cur_proc));
			parser->status = FALSE;
			cur_proc = get_process();
			tmp = tmp->next;
			continue ;
		}
		if (parser->status == FALSE)
			err = parse_init(tmp_token, parser);
		else if (parser->status == PAR_STRING
		||	parser->status == PAR_QUOTATION
		||	parser->status == PAR_APOSTROPHE
		||	parser->status == PAR_ENV)
			err = parse_string(tmp_token, parser);
		if (parser->status == PAR_REDIRECT)
			err = parse_redirect(tmp_token, parser, cur_proc);
		tmp = tmp->next;
	}
	argv_list_to_split(cur_proc, parser);
	ft_lstadd_back(&processes, ft_lstnew(cur_proc));
	return (err);
}

void	free_process(t_process *process)
{
	free_split(process->cmd);
	ft_lstclear(&(process->redir_in), free);
	ft_lstclear(&(process->redir_out), free);
}

void	free_process_list(t_list *processes)
{
	t_list		*tmp;
	t_process	*cur_proc;

	tmp = processes->next;
	while (tmp != NULL)
	{
		cur_proc = tmp->content;
		free_process(cur_proc);
		tmp = tmp->next;
	}
	ft_lstclear(&processes, free);
	free(processes);
}

t_list *parse(t_list *envl, char *input)
{
	t_list		*tokens;
	t_parser	*parser;
	t_list		*processes;

	tokens = get_processed_tokens(envl, input);
	if (tokens == NULL)
	{
		free_tokens(&tokens);
		printf("invalid env!\n");
		return (NULL);
	}
	// if (check_syntax(tokens) == ERR_TRUE)
	// {
	// 	free_tokens(&tokens);
	// 	printf("syntax error occurred!\n");
	// 	return (NULL);
	// }
	join_tokens(tokens);
	parser = get_parser();
	processes = ft_lstnew(NULL);
	if (parse_tokens(tokens, processes, parser) == ERR_TRUE)
	{
		free_tokens(&tokens);
		free_parser(&parser);
		free_process_list(processes);
		printf("parse error occurred!\n");
		return (NULL);
	}
	free_tokens(&tokens);
	free_parser(&parser);
	return (processes);
}

//해당 토큰에 따라 상태를 갖는다.
//seperated 플래그를 통해 붙일지 말지를 정한다.