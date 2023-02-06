/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:45:06 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 15:25:19 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	seperate_process_by_pipe(t_process **proc, t_parser *parser,
								t_list *processes)
{
	argv_list_to_split(*proc, parser);
	ft_lstadd_back(&processes, ft_lstnew(*proc));
	parser->status = FALSE;
	*proc = get_process();
}

int	is_parser_string_status(t_parser *parser)
{
	return (parser->status == PAR_STRING \
		|| parser->status == PAR_QUOTATION \
		|| parser->status == PAR_APOSTROPHE \
		|| parser->status == PAR_ENV);
}

void	parse_by_type(t_token *token, t_parser *parser,
					t_process *proc, int *err)
{
	if (parser->status == FALSE)
		*err = parse_init(token, parser);
	else if (is_parser_string_status(parser) == TRUE)
		*err = parse_string(token, parser);
	if (parser->status == PAR_REDIRECT)
		*err = parse_redirect(token, parser, proc);
}

int	parse_tokens(t_list *tokens, t_list *processes, t_parser *parser)
{
	t_list		*tmp;
	t_token		*tmp_token;
	t_process	*cur_proc;
	int			err;

	tmp = tokens->next;
	cur_proc = get_process();
	err = ERR_FALSE;
	while (tmp != NULL)
	{
		tmp_token = tmp->content;
		if (tmp_token->status == PAR_PIPE)
		{
			seperate_process_by_pipe(&cur_proc, parser, processes);
			tmp = tmp->next;
			continue ;
		}
		parse_by_type(tmp_token, parser, cur_proc, &err);
		tmp = tmp->next;
	}
	argv_list_to_split(cur_proc, parser);
	ft_lstadd_back(&processes, ft_lstnew(cur_proc));
	return (err);
}

void	free_redir_list(t_list	**redir)
{
	t_list	*tmp;
	t_redir	*tmp_redir;

	tmp = (*redir)->next;
	while (tmp != NULL)
	{
		tmp_redir = tmp->content;
		free(tmp_redir->file);
		tmp = tmp->next;
	}
	ft_lstclear(redir, free);
	free(*redir);
}
