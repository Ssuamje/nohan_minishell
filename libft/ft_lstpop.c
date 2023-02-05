/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:54:28 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 19:42:46 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#define LEFT 0
#define RIGHT 1

static	t_list	*get_left_addr(t_list *lst, t_list *beside)
{
	t_list	*tmp;

	tmp = lst;
	lst = lst->next;
	while (lst != NULL)
	{
		if (lst == beside)
			return (tmp);
		tmp = lst;
		lst = lst->next;
	}
	return (NULL);
}

t_list	*ft_lstpop(t_list *lst, t_list *to_pop, int return_dir)
{
	t_list	*left;
	t_list	*right;

	if (to_pop == NULL || lst == NULL)
		return (NULL);
	left = get_left_addr(lst, to_pop);
	right = to_pop->next;
	left->next = right;
	ft_lstdelone(to_pop, free);
	if (return_dir == LEFT && left != NULL)
		return (left);
	if (return_dir == RIGHT && right != NULL)
		return (right);
	return (NULL);
}
