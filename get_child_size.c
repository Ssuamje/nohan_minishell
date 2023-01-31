/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_child_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:12:40 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 16:34:32 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_child_size(t_proc *proc)
{
	t_proc	*tmp;
	int		size;

	tmp = proc;
	size = 0;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
