/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:27:25 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/04 20:09:42 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	builtin_cd(t_process *cur)
{
	if (cur->cmd[1] == NULL || ft_strcmp(cur->cmd[1], "~"))
	{
		if (find_env_by_key(g_envl, "HOME") == NULL)
			printf("cd: HOME not set\n");
		else
			chdir(getenv("HOME"));
	}
	else
		if (chdir(cur->cmd[1]) == -1)
			printf("cd: %s: No such file or directory\n", cur->cmd[1]);
}
