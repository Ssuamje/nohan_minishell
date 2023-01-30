/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:19:22 by sanan             #+#    #+#             */
/*   Updated: 2023/01/30 23:26:34 by sanan            ###   ########.fr       */
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
	if (parser->flag_redir == REDIR_L
	||	parser->flag_redir == REDIR_LL)
		ft_lstadd_back(&(cur_proc->redir_in), ft_lstnew(get_redir(parser)));
	if (parser->flag_redir == REDIR_R
	||	parser->flag_redir == REDIR_RR)
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
	while (split[idx] != NULL && cmd_list != NULL)
	{
		split[idx] = ft_strdup(cmd_list->content);
		idx++;
		cmd_list = cmd_list->next;
	}
	cur_proc->cmd = split;
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
		if (parser->status == PAR_STRING
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

#define REDIR_IN 0
#define REDIR_OUT 1

void	print_redir(t_list *redir_list)
{
	t_list	*tmp;
	t_redir	*cur;

	tmp = redir_list->next;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur = tmp->content;
		if (cur->flag == REDIR_L)
			printf("	{ type : <\n");
		if (cur->flag == REDIR_LL)
			printf("	{ type : <<\n");
		if (cur->flag == REDIR_R)
			printf("	{ type : >\n");
		if (cur->flag == REDIR_RR)
			printf("	{ type : >>\n");
		printf("  	file = _%s_}\n", cur->file);
		printf("\n");
		tmp = tmp->next;
	}
}

void	print_processes(t_list *processes)
{
	t_list		*tmp;
	int			idx;
	t_process	*cur;

	tmp = processes->next;
	idx = 0;
	while (tmp != NULL && tmp->content != NULL)
	{
		cur = tmp->content;
		printf("**********process %d**********\n", idx);
		print_redir(cur->redir_in);
		print_redir(cur->redir_out);
		print_split(cur->cmd);
		idx++;
		tmp = tmp->next;
	}
}

t_list *parse(char **envp, char *input)
{
	t_list		*tokens;
	t_parser	*parser;
	t_list		*processes;

	tokens = get_processed_tokens(envp, input);
	if (tokens == NULL)
	{
		free_tokens(&tokens);
		printf("invalid env!\n");
		return (NULL);
	}
	if (check_syntax(tokens) == ERR_TRUE)
	{
		free_tokens(&tokens);
		printf("syntax error occurred!\n");
		return (NULL);
	}
	join_tokens(tokens);
	print_token(tokens);
	parser = get_parser();
	processes = ft_lstnew(NULL);
	if (parse_tokens(tokens, processes, parser) == ERR_TRUE)
	{
		free_tokens(&tokens);
		free_parser(&parser);
		ft_lstclear(&processes, free); // need to be strict
		printf("parse error occurred!\n");
		return (NULL);
	}
	free_tokens(&tokens);
	free_parser(&parser);
	return (processes);
}

//해당 토큰에 따라 상태를 갖는다.
//seperated 플래그를 통해 붙일지 말지를 정한다.