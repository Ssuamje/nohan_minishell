/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:07:27 by hyungnoh          #+#    #+#             */
/*   Updated: 2022/11/17 18:48:40 by hyungnoh         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reduce_line(void (*del)(void *), t_list *result, void *tmp)
{
	del(tmp);
	ft_lstclear(&result, del);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*curr;
	void	*tmp;

	if (!lst || !f || !del)
		return (0);
	result = 0;
	while (lst)
	{
		tmp = f(lst->content);
		if (!tmp)
		{
			ft_lstclear(&result, del);
			return (0);
		}
		curr = ft_lstnew(tmp);
		if (!curr)
		{
			reduce_line(del, result, tmp);
			return (0);
		}
		ft_lstadd_back(&result, curr);
		lst = lst->next;
	}
	return (result);
}
