/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:16:28 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 15:05:29 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

int	is_unset_syntax_error(char *cmd)
{
	return ((ft_strcmp(cmd, "") == TRUE) \
	|| (ft_isdigit(cmd[0]) == TRUE) \
	|| (is_in_charset(cmd[0], "`~!@#%$%^&*(){}\\|-\'\";:+,.=?/")) \
	|| (is_cmd_has_special_after_builtin(cmd)));
}

int	builtin_unset(char **cmd, t_list *envl)
{
	int	idx;

	idx = 1;
	set_exit_code(g_global->g_envl, 0);
	if (cmd[1] == NULL)
		return (1);
	else
	{
		while (cmd[idx] != NULL)
		{
			if (is_unset_syntax_error(cmd[idx]) == TRUE)
			{
				printf("AengMuShell $ unset: `%s\': not a valid identifier\n", \
					cmd[idx++]);
				set_exit_code(g_global->g_envl, 1);
				continue ;
			}
			delete_env_by_key(envl, cmd[idx++]);
		}
	}
	sort_envl(envl);
	return (1);
}
