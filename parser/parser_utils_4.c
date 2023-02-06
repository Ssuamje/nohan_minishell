/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:39:12 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 15:33:06 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_redir	*get_redir(t_parser *parser)
{
	t_redir	*to_return;

	to_return = malloc(sizeof(t_redir));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->flag = parser->flag_redir;
	to_return->file = ft_strdup(parser->string);
	return (to_return);
}

void	put_redir_token(t_parser *parser, t_process *cur_proc)
{
	if (ft_strcmp(parser->string, "<") \
		|| ft_strcmp(parser->string, "<<") \
		|| ft_strcmp(parser->string, ">") \
		|| ft_strcmp(parser->string, ">>"))
		return ;
	if (parser->flag_redir == IN_TRUNC \
	|| parser->flag_redir == IN_APPEND)
		ft_lstadd_back(&(cur_proc->redir_in), ft_lstnew(get_redir(parser)));
	if (parser->flag_redir == OUT_TRUNC \
	|| parser->flag_redir == OUT_APPEND)
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
	if (token->status == PAR_PIPE)
		return (ERR_TRUE);
	if (token->string[0] != '<' \
	&& token->string[1] != '>')
	{
		if (parser->string)
			free(parser->string);
		parser->string = ft_strdup(token->string);
		put_redir_token(parser, cur_proc);
	}
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
	if (split == NULL)
		exit_error(ERR_MALLOC);
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
