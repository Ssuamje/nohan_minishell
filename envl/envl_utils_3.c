/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:02:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 14:25:52 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envl.h"

int	longer_len(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 > len_s2)
		return (len_s1);
	else
		return (len_s2);
}

void	swap_content(t_list *left, t_list *right)
{
	t_environ	*tmp;

	tmp = right->content;
	right->content = left->content;
	left->content = tmp;
}

void	sort_bubble_list(t_list *envl)
{
	t_list		*tmp;
	t_environ	*tmp_env;
	t_environ	*next_env;

	tmp = envl;
	while (tmp->next != NULL)
	{
		tmp_env = tmp->content;
		next_env = tmp->next->content;
		if (ft_strncmp(tmp_env->key, next_env->key, \
			longer_len(tmp_env->key, next_env->key)) > 0)
			swap_content(tmp, tmp->next);
		tmp = tmp->next;
	}
}

void	sort_envl(t_list *envl)
{
	int	size;

	size = ft_lstsize(envl->next);
	while (size - 1 > 0)
	{
		sort_bubble_list(envl->next);
		size--;
	}
}
