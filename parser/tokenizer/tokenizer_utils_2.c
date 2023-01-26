/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:55:54 by sanan             #+#    #+#             */
/*   Updated: 2023/01/26 13:31:48 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

void	process_token_list_env(char **envp, t_list *token_list)
{
	t_list	*tmp_node;
	t_token	*tmp_token;

	tmp_node = token_list->next;
	tmp_token = NULL;
	while (tmp_node != NULL && tmp_node->content != NULL)
	{
		tmp_token = tmp_node->content;
		process_env(envp, tmp_token);
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
