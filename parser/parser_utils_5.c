/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:41:54 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:09:44 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	check_syntax_by_type(t_token *token, int *err)
{
	if (token->status == PAR_STRING)
		*err = syntax_string(token);
	if (token->status == PAR_REDIRECT)
		*err = syntax_redirect(token);
	if (token->status == PAR_QUOTATION
		|| token->status == PAR_APOSTROPHE)
		*err = syntax_quotes(token);
	if (token->status == PAR_PIPE)
		*err = syntax_pipe(token);
	if (token->status == PAR_ENV)
		*err = syntax_env(token);
}

int	check_available_type(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;
	t_token	*next_token;

	tmp = tokens->next;
	while (tmp->next != NULL)
	{
		tmp_token = tmp->content;
		next_token = tmp->next->content;
		if (((tmp_token->status == PAR_REDIRECT) && \
			(next_token->status == PAR_REDIRECT)) \
		|| ((tmp_token->status == PAR_PIPE) && \
			(next_token->status == PAR_PIPE)) \
		|| ((tmp_token->status == PAR_REDIRECT) && \
			(next_token->status == PAR_PIPE)))
			return (FALSE);
		tmp = tmp->next;
	}
	tmp_token = tmp->content;
	if ((tmp_token->status == PAR_PIPE) \
	|| (tmp_token->status == PAR_REDIRECT))
		return (FALSE);
	return (TRUE);
}

int	check_syntax(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;
	int		err;

	tmp = tokens->next;
	if ((check_first_arg(tmp->content) == ERR_TRUE) \
	|| (check_available_type(tokens) == FALSE))
		return (ERR_TRUE);
	while (tmp != NULL)
	{
		tmp_token = tmp->content;
		check_syntax_by_type(tmp_token, &err);
		if (err == ERR_TRUE)
			return (ERR_TRUE);
		tmp = tmp->next;
	}
	return (TRUE);
}

void	free_process(t_process *process)
{
	free_split(process->cmd);
	free_redir_list(&(process->redir_in));
	free_redir_list(&(process->redir_out));
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
