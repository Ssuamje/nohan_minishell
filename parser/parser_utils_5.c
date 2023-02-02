/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:41:54 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 19:45:24 by sanan            ###   ########.fr       */
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
