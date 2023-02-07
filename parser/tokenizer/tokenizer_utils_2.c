/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:55:54 by sanan             #+#    #+#             */
/*   Updated: 2023/02/07 16:15:15 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

char	*remove_quote_apost(char *string, char c, int *flag)
{
	int		start;
	int		end;
	char	*result;
	char	*trimmed;
	char	*white;

	start = 0;
	*flag = TRUE;
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
	free_double(white, trimmed);
	return (result);
}

void	check_set_token_properties(t_token *token)
{
	if (token->string[0] == ' ' || token->string[0] == '\t')
		token->is_seperated = TRUE;
}

void	lstrip_once(char **string)
{
	char	*tmp;

	tmp = *string;
	if ((*string[0] == ' ') || (*string[0] == '\t'))
	{
		*string = ft_strdup(*string + 1);
		free(tmp);
	}
}

void	check_string_condition(t_token *token)
{
	char	*tmp;
	int		flag_trim;

	tmp = token->string;
	flag_trim = FALSE;
	check_set_token_properties(token);
	if (token->status == LEX_APOSTROPHE)
		token->string = remove_quote_apost(token->string, '\'', &flag_trim);
	if (token->status == LEX_QUOTATION)
		token->string = remove_quote_apost(token->string, '\"', &flag_trim);
	if (flag_trim == TRUE)
		free(tmp);
	if (token->is_seperated == TRUE)
		lstrip_once(&(token->string));
	if (token->status == LEX_STRING)
		lstrip_once(&(token->string));
}

int	process_tokens_env(t_list *envl, t_list *tokens)
{
	t_list	*tmp_node;
	t_token	*tmp_token;

	tmp_node = tokens->next;
	tmp_token = NULL;
	while (tmp_node != NULL && tmp_node->content != NULL)
	{
		tmp_token = tmp_node->content;
		check_string_condition(tmp_token);
		if (process_env(envl, tmp_token) == FALSE)
			return (FALSE);
		tmp_node = tmp_node->next;
	}
	return (TRUE);
}
