/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:10:58 by sanan             #+#    #+#             */
/*   Updated: 2023/02/02 20:22:17 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstreplace(t_list **list)
{
	t_list	*tmp;
	t_list	*next;

	if (list == NULL || *list == NULL)
		return ;
	tmp = *list;
	while (tmp->next != NULL)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*list = ft_lstnew(NULL);
}
