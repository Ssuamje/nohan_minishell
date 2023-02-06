/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:01:19 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 12:01:50 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	print_split(char **split)
{
	int	idx;

	idx = 0;
	if (split == NULL)
		return ;
	printf("*************printing split***********\n");
	while (split[idx] != NULL)
	{
		printf("_%s_\n", split[idx]);
		idx++;
	}
	printf("\n");
}
