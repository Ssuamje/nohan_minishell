/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_child_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:12:40 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/01/31 20:13:10 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/ssuamje/minishell/include/minishell.h"

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
