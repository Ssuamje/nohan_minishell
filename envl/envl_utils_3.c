/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:02:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 14:08:00 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envl.h"

void	swap_list(t_list *left, t_list *right)
{
	t_list	*tmp;

	tmp = right->next;
	right->next = left;
	left->next = right;
}

void	sort_bubble_list(t_list *envl)
{
	int	size;

	size = ft_lstsize(envl) - 1;
}

void	sort_envl(t_list *envl)
{
	int	size;

	size = ft_lstsize(envl) - 1;

	while (size - 1 > 0)
	{
		sort_bubble_list(envl);
		size--;
	}
}
