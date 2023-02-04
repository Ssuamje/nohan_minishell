/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:16:28 by sanan             #+#    #+#             */
/*   Updated: 2023/02/03 16:23:33 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

int	is_unset_syntax_error(char *cmd)
{
	return ((ft_strcmp(cmd, "") == TRUE) \
	|| (ft_isdigit(cmd[0]) == TRUE) \
	|| (is_cmd_has_special_after(cmd)));
}

void	builtin_unset(char **cmd, t_list *envl)
{
	int	idx;

	idx = 1;
	if (cmd[1] == NULL)
		return ;
	else
	{
		while (cmd[idx] != NULL)
		{
			if (is_unset_syntax_error(cmd[1]) == TRUE)
			{
				printf("unset: `%s\': not a valid identifier\n", cmd[idx]);
				return ;
			}
			delete_env_by_key(envl, cmd[idx++]);
		}
	}
}