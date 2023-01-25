/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:23:59 by sanan             #+#    #+#             */
/*   Updated: 2023/01/25 15:16:03 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tokenizer.h"

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

char *ft_strldup(char *src, int len)
{
	char	*dest;
	int		src_len;
	int		dest_len;
	int		idx;

	if (src == NULL)
		return (NULL);
	idx = 0;
	src_len = ft_strlen(src);
	if (src_len > len)
		dest_len = len;
	else
		dest_len = src_len;
	dest = malloc(sizeof(char) * (dest_len + 1));
	while (idx < dest_len && src[idx] != '\0')
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (dest);
}

char *get_env_string(char *input, int idx_env)
{
	int idx;
	char *to_return;

	idx = idx_env;
	while (input[idx] != '\0' \
		&& is_special(input[idx]) == FALSE)
		idx++;
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

char *process_env(char **envp, char *input)
{
	int	idx_env;
	char *to_find;

	idx_env = get_env_idx(input); // '$' 다음 인덱스, 없으면 -1
	if (idx_env == -1)
		return (NULL);
	if (is_num(input[idx_env]) \
		|| input[idx_env] == '\0')
		return (NULL); // syntax error
	to_find = get_env_string(input, idx_env);
	interpret_env(envp, &to_find);
	return (to_find);
}