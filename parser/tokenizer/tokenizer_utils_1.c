/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:23:59 by sanan             #+#    #+#             */
/*   Updated: 2023/01/25 16:20:03 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

int	get_env_idx(char *string)
{
	int idx;

	idx = 0;
	while (string[idx] != '\0'
		&& string[idx] != '$')
		idx++;
	if (string[idx] == '\0')
		return (-1);
	return (idx + 1);
}

char *get_env_string(char *input, int idx_env)
{
	int idx;
	char *to_return;

	idx = idx_env;
	while (input[idx] != '\0' \
		&& is_special(input[idx]) == FALSE)
		idx++;
	if (is_special(input[idx]) == TRUE)
		return (NULL);
	to_return = ft_strldup(&(input[idx_env]), (idx - idx_env));
	return (to_return);
}

void interpret_env(char **envp, char **to_find)
{
	int		idx;
	int		to_find_len;
	char	*env_start;
	int		env_len;

	idx = 0;
	while (envp[idx] != NULL)
	{
		to_find_len = ft_strlen(*to_find);
		if (ft_strncmp(envp[idx], *to_find, to_find_len) == 0 \
			&& envp[idx][to_find_len] == '=')
		{
			free(*to_find);
			env_start = &(envp[idx][to_find_len + 1]);
			env_len = ft_strlen(env_start);
			*to_find = ft_strldup(env_start, env_len);
			return ;
		}
		idx++;
	}
	free(*to_find);
	*to_find = ft_strdup("");
}

char	*join_env(char *input, int idx_env, char *env_string)
{
	int env_len;
	char *to_return;

	env_len = ft_strlen(env_string);
	to_return = malloc(sizeof(char) * (idx_env + env_len));
	to_return[idx_env + env_len] = '\0';
	ft_memcpy(to_return, input, idx_env - 1);
	ft_memcpy(&to_return[idx_env - 1], env_string, env_len);
	return (to_return);
}

char	*process_env(char **envp, char *input)
{
	int	idx_env;
	char *env_string;
	char *processed_string;

	idx_env = get_env_idx(input); // '$' 다음 인덱스, 없으면 -1
	if (idx_env == -1)
		return (ft_strdup(input));
	if (is_num(input[idx_env]) \
		|| input[idx_env] == '\0')
		return (NULL); // syntax error
	env_string = get_env_string(input, idx_env);
	interpret_env(envp, &env_string);
	processed_string = join_env(input, idx_env, env_string);
	free(env_string);
	return (processed_string);
}
