/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:28:26 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 12:53:01 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

#define ENV_NONE -1
#define ENV_SYNTAX_ERROR 0
#define ENV_SUCCESS 1

int	is_dont_need_interpret(char	*string)
{
	if ((string[0] == '$') && \
			((string[1] == '\0') || \
			(is_special(string[1]) == TRUE) || \
			(ft_isdigit(string[1]) == TRUE)))
		return (TRUE);
	return (FALSE);
}

char	*chunk_string(t_list **getter)
{
	t_list	*tmp;
	char	*cur;
	char	*chunk;
	int		size;
	int		idx;

	tmp = (*getter)->next;
	size = ft_lstsize(*getter) - 1;
	chunk = malloc(sizeof(char) * (size + 1));
	if (chunk == NULL)
		exit_error(ERR_MALLOC);
	chunk[size] = '\0';
	idx = 0;
	while (tmp != NULL)
	{
		cur = tmp->content;
		chunk[idx++] = *cur;
		tmp = tmp->next;
	}
	ft_lstclear(getter, free);
	*getter = ft_lstnew(NULL);
	return (chunk);
}

char	**list_to_split(t_list **str_list)
{
	int		size;
	t_list	*tmp;
	char	*tmp_str;
	char	**to_return;
	int		idx;

	tmp = (*str_list)->next;
	size = ft_lstsize(*str_list) - 1;
	to_return = malloc(sizeof(char *) * (size + 1));
	if (to_return == NULL)
		exit_error(ERR_MALLOC);
	to_return[size] = NULL;
	idx = 0;
	while (idx < size)
	{
		tmp_str = tmp->content;
		to_return[idx++] = ft_strdup(tmp_str);
		tmp = tmp->next;
	}
	ft_lstclear(str_list, free);
	free(*str_list);
	return (to_return);
}

char	**split_env_with_dollar(char *str)
{
	int		idx;
	t_list	*getter;
	t_list	*str_list;

	getter = ft_lstnew(NULL);
	str_list = ft_lstnew(NULL);
	idx = 0;
	while (str[idx])
	{
		if ((str[idx] == '$' \
		&& ft_lstsize(getter) > 1) \
		|| ((str[idx] == '?') && ft_lstsize(getter) > 2))
		{
			ft_lstadd_back(&str_list, ft_lstnew(chunk_string(&getter)));
			ft_lstadd_back(&getter, ft_lstnew(ft_strdup(&str[idx])));
		}
		else
			ft_lstadd_back(&getter, ft_lstnew(ft_strdup(&str[idx])));
		idx++;
	}
	ft_lstadd_back(&str_list, ft_lstnew(chunk_string(&getter)));
	ft_lstclear(&getter, free);
	free(getter);
	return (list_to_split(&str_list));
}

int	process_env_split_and_join(char **env_splitted, \
								t_list *envl, char **processed_string)
{
	int		idx;
	char	*tmp;

	idx = 0;
	if (env_splitted == NULL)
		return (ENV_SYNTAX_ERROR);
	while (env_splitted[idx] != NULL)
	{
		if (env_splitted[idx][0] == '$' \
		&& ((env_splitted[idx][1] != '\0' && \
			is_special(env_splitted[idx][1]) == FALSE)))
			interpret_env(envl, &env_splitted[idx]);
		tmp = *processed_string;
		if (env_splitted[idx] != NULL)
		{
			*processed_string = \
			ft_strjoin(*processed_string, env_splitted[idx++]);
			free(tmp);
		}
	}
	return (ENV_SUCCESS);
}
