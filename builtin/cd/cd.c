/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:27:25 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/04 12:00:15 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	builtin_cd(t_process *cur)
{
	if (cur->cmd[1] == NULL || ft_strcmp(cur->cmd[1], "~"))
		chdir(getenv("HOME"));
	else
		chdir(cur->cmd[1]);
}
