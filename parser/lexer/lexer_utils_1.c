/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:31:58 by sanan             #+#    #+#             */
/*   Updated: 2023/01/24 15:34:17 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

t_lexer	*get_lexer(void)
{
	t_lexer	*to_return;

	to_return = malloc(sizeof(t_lexer));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return->env_buffer = NULL;
	to_return->str_buffer = NULL;
	to_return->status = LEX_NORMAL;
	return (to_return);
}

void	add_char_to_buffer(char *c, t_lexer *lexer)
{
	if (lexer->status == LEX_ENV)
		ft_lstadd_back(&(lexer->env_buffer), ft_lstnew(c));
	else
		ft_lstadd_back(&(lexer->str_buffer), ft_lstnew(c));
}

char	*buffer_to_string(t_list *buffer)
{
	int		len;
	char	*string;
	t_list	*tmp;

	len = ft_lstsize(buffer);
	string = malloc(sizeof(char) * (len + 1));
	string[len] = '\0';
	tmp = buffer;
	len = 0;
	while (tmp != NULL)
	{
		string[len++] = *((char *)tmp->content);
		tmp = tmp->next;
	}
	return (string);
}

void	flush_buffer(t_lexer *lexer)
{
	ft_lstclear(&(lexer->env_buffer), free);
	ft_lstclear(&(lexer->str_buffer), free);
}

char	*get_processed_string(t_lexer *lexer)
{
	char	*env_string;
	char	*string;
	char	*to_return;

	env_string = NULL;
	if (lexer->status != LEX_APOSTROPHE)
		env_string = buffer_to_string(lexer->env_buffer);
	string = buffer_to_string(lexer->str_buffer);
	to_return = ft_strjoin(string, env_string);
	if (env_string)
		free(env_string);
	free(string);
	flush_buffer(lexer);
	return (to_return);
}
