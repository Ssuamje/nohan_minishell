/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:55:54 by sanan             #+#    #+#             */
/*   Updated: 2023/01/26 22:36:21 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

int		count_char(char *string, char c)
{
	int idx;
	int count;

	idx = 0;
	count = 0;
	while (string[idx] != '\0')
	{
		if (string[idx] == c)
			count++;
		idx++;
	}
	return (count);
}

char	*trim_once(char *string, char c)
{
	int		start;
	int		end;
	char	*result;
	char	*trimmed;
	char 	*white;

	start = 0;
	if (count_char(string, c) < 2)
		return (ft_strdup(string));
	end = ft_strlen(string) - 2;
	while (start < end && string[start] != c)
		start++;
	if (string[0] == '\0')
		return (ft_calloc(1, sizeof(char)));
	if (c == '\0')
		return (ft_strdup(string));
	trimmed = ft_strldup(&string[start + 1], end - start);
	white = ft_strdup(" ");
	if (start > 0)
		result = ft_strjoin(white, trimmed);
	else
		result = ft_strdup(trimmed);
	free(white);
	free(trimmed);
	return (result);
}

void	process_token_list_env(char **envp, t_list *token_list)
{
	t_list	*tmp_node;
	t_token	*tmp_token;
	char	*tmp;

	tmp_node = token_list->next;
	tmp_token = NULL;
	while (tmp_node != NULL && tmp_node->content != NULL)
	{
		tmp_token = tmp_node->content;
		if (tmp_token->status == LEX_APOSTROPHE)
		{
			tmp = tmp_token->string;
			tmp_token->string = trim_once(tmp_token->string, '\'');
			free(tmp);
		}
		if (tmp_token->status == LEX_QUOTATION)
		{
			tmp = tmp_token->string;
			tmp_token->string = trim_once(tmp_token->string, '\"');
			free(tmp);
		}
		printf("trimmed = %s\n", tmp_token->string);
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
