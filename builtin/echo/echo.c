/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 01:36:30 by hyungseok         #+#    #+#             */
/*   Updated: 2023/02/09 15:22:13 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

void	check_n(t_process *cur, int flag, int *i, int *j)
{
	*i = 0;
	while (cur->cmd[++(*i)] != NULL)
	{
		*j = 0;
		if (cur->cmd[*i][(*j) + 1] == '\0')
			break ;
		while (cur->cmd[*i][++(*j)] != '\0')
		{
			if (cur->cmd[*i][*j] != 'n' || cur->cmd[*i][0] != '-')
			{
				flag = 1;
				break ;
			}
		}
		if (flag == 1)
			break ;
	}
}

void	builtin_echo(t_process *cur)
{
	int	i;
	int	j;

	if (cur->cmd[1] == NULL \
	|| cur->cmd[1][0] == '\0')
	{
		ft_putstr("\n");
		exit(0);
	}
	check_n(cur, 0, &i, &j);
	i--;
	j = i;
	while (cur->cmd[++i] != NULL)
	{
		ft_putstr(cur->cmd[i]);
		if (cur->cmd[i + 1] != NULL)
			ft_putstr(" ");
	}
	if (j == 0)
		ft_putstr("\n");
	exit(0);
}
