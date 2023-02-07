/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:35:04 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/07 17:54:07 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	interpret_cur_file(t_process *cur)
{
	char	*tmp;
	int		i;

	i = -1;
	while (cur->cmd[++i] != NULL)
	{
		if (ft_strncmp(cur->cmd[i], "~/", 2) == 0 || ft_strcmp(cur->cmd[i], "~"))
		{
			tmp = cur->cmd[i];
			cur->cmd[i] = ft_join_and_free(get_value_by_key(g_global->g_envl, "HOME"), \
					ft_join_and_free(ft_strdup("/"), ft_strdup(&(cur->cmd[i][2]))));
			free(tmp);
		}
	}
}
