/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:55:54 by sanan             #+#    #+#             */
/*   Updated: 2023/01/30 14:28:38 by sanan            ###   ########.fr       */
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

char	*remove_quote_apost(char *string, char c, int *flag)
{
	int		start;
	int		end;
	char	*result;
	char	*trimmed;
	char 	*white;

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
	free(white);
	free(trimmed);
	return (result);
}

void	check_set_token_properties(t_token *token)
{
	if (token->string[0] == ' ' || token->string[0] == ' ')
		token->is_seperated = TRUE;
}

char	*lstrip_once(char *string)
{
	char *stripped;

	if ((string[0] != ' ') && (string[0] != '\t'))
		stripped = ft_strdup(string);
	else
		stripped = ft_strdup(&string[1]);
	free(string);
	return (stripped);
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
	if (token->is_seperated == TRUE)
		token->string = lstrip_once(token->string);
	if (flag_trim == TRUE)
		free(tmp);
}

int	process_tokens_env(char **envp, t_list *tokens)
{
	t_list	*tmp_node;
	t_token	*tmp_token;

	tmp_node = tokens->next;
	tmp_token = NULL;
	while (tmp_node != NULL && tmp_node->content != NULL)
	{
		tmp_token = tmp_node->content;
		check_string_condition(tmp_token);
		if (process_env(envp, tmp_token) == FALSE)
			return(FALSE);
		tmp_node = tmp_node->next;
	}
	return (TRUE);
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

t_list *get_processed_tokens(char** envp, char *input)
{
	t_lexer	*lexer;
	t_list	*tokens;
	
	lexer = get_lexer();
	tokens = tokenize(input, lexer);
	if (process_tokens_env(envp, tokens) == FALSE)
	{
		if (tokens)
			free_tokens(&tokens);
		free(lexer);
		return (NULL);
	}
	free(lexer);
	return (tokens);
}
