/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:16:28 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 16:47:11 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

int	is_unset_syntax_error(char *cmd)
{
	return ((ft_strcmp(cmd, "") == TRUE) \
	|| (ft_isdigit(cmd[0]) == TRUE) \
	|| (is_in_charset(cmd[0], "`~!@#%$^&*(){}\\|-\'\";:+,.=?")) \
	|| (is_cmd_has_special_after(cmd)));
}

int	builtin_unset(char **cmd, t_list *envl)
{
	int	idx;

	idx = 1;
	if (cmd[1] == NULL)
		return (1);
	else
	{
		while (cmd[idx] != NULL)
		{
			if (is_unset_syntax_error(cmd[idx]) == TRUE)
			{
				printf("AengMuShell $ unset: `%s\': not a valid identifier\n", \
					cmd[idx]);
				idx++;
				continue ;
			}
			delete_env_by_key(envl, cmd[idx++]);
		}
	}
	// sort_envl(envl);
	return (1);
}
