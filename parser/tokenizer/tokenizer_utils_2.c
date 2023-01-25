/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:55:54 by sanan             #+#    #+#             */
/*   Updated: 2023/01/25 16:13:41 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

void	process_token_list_env(char **envp, t_list *token_list)
{
	t_list	*tmp_node;
	t_token	*tmp_token;
	char	*tmp_string;

	tmp_node = token_list->next;
	while (tmp_node != NULL)
	{
		tmp_token = tmp_node->content;
		if (tmp_token == NULL)
			break ;
		tmp_string = tmp_token->string;
		tmp_token->string = process_env(envp, tmp_token->string);
		free(tmp_string);
		tmp_node = tmp_node->next;
	}
}


void	print_envp(char **envp)
{
	char *tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		printf("%s\n", tmp);
		envp++;
		tmp = *envp;
	}
}
