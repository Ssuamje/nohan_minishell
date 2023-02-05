/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:10:58 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 19:42:56 by hyungnoh         ###   ########.fr       */
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
