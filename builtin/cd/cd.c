/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:27:25 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/03 15:29:05 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	builtin_cd(t_process *cur)
{
	if (cur->cmd[1] == NULL || ft_strcmp(cur->cmd[1], "~"))
		chdir("/Users/hyungnoh");
	else
		chdir(cur->cmd[1]);
}
