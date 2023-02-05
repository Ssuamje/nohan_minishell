/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:16:47 by sanan             #+#    #+#             */
/*   Updated: 2022/11/10 22:36:29 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*error_lstclear(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node_temp;
	t_list	*lst_result;
	void	*content_temp;

	if (!lst || !f || !del)
		return (0);
	lst_result = 0;
	while (lst)
	{
		content_temp = f(lst->content);
		if (!content_temp)
			return (error_lstclear(lst_result, del));
		node_temp = ft_lstnew(content_temp);
		if (!node_temp)
		{
			del(content_temp);
			return (error_lstclear(lst_result, del));
		}
		ft_lstadd_back(&lst_result, node_temp);
		lst = lst->next;
	}
	return (lst_result);
}
