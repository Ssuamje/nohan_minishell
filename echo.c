/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 01:36:30 by hyungseok         #+#    #+#             */
/*   Updated: 2023/02/03 02:38:15 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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

void	echo(t_process *cur)
{
	int	i;
	int	j;

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
