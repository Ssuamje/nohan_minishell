/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:56:23 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 21:10:13 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envl.h"

void	print_envl(t_list *envl)
{
	t_list		*tmp;
	t_environ	*tmp_env;

	tmp = envl->next;
	while (tmp != NULL)
	{
		tmp_env = tmp->content;
		if (ft_strcmp(tmp_env->key, "?") == FALSE)
		{
			printf("declare -x ");
			printf("%s=%s\n", tmp_env->key, tmp_env->value);
		}
		tmp = tmp->next;
	}
}

int	get_idx_equal(char *env)
{
	int	idx;

	idx = 0;
	while (env[idx] != '\0')
	{
		if (env[idx] == '=')
			return (idx);
		idx++;
	}
	return (-1);
}

void	set_key_value(char **key_value, int idx_equal, char *env)
{
	int	env_len;

	env_len = ft_strlen(env);
	key_value[0] = malloc(sizeof(char) * (idx_equal + 1));
	if (key_value[0] == NULL)
		exit_error(ERR_MALLOC);
	ft_strlcpy(key_value[0], env, idx_equal + 1);
	key_value[1] = malloc(sizeof(char) * (env_len - idx_equal + 1));
	if (key_value[1] == NULL)
		exit_error(ERR_MALLOC);
	ft_strlcpy(key_value[1], &env[idx_equal + 1], (env_len - idx_equal + 1));
}

void	add_env_to_list(t_list *envl, char *env)
{
	int			idx_equal;
	char		*key_value[2];
	t_environ	*content;

	idx_equal = get_idx_equal(env);
	set_key_value(key_value, idx_equal, env);
	if (is_key_in_envl(envl, key_value[0]) == FALSE)
	{
		content = malloc(sizeof(t_environ));
		content->key = ft_strdup(key_value[0]);
		free(key_value[0]);
		content->value = ft_strdup(key_value[1]);
		free(key_value[1]);
		ft_lstadd_back(&envl, ft_lstnew(content));
	}
	else
	{
		content = find_env_by_key(envl, key_value[0]);
		free(content->value);
		content->value = ft_strdup(key_value[1]);
	}
}

t_list	*map_envp_to_list(char **envp)
{
	t_list	*envl;
	int		idx;

	envl = ft_lstnew(NULL);
	idx = 0;
	while (envp[idx] != NULL)
	{
		add_env_to_list(envl, envp[idx]);
		idx++;
	}
	return (envl);
}
