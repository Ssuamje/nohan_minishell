/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:26:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:54:34 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	is_cmd_has_special_after_builtin(char *cmd)
{
	int	idx;

	idx = 0;
	while (cmd[idx] != '\0' && cmd[idx] != '=')
	{
		if (is_in_str(cmd[idx], "`~!#%^&*(){}\\ |\'\";") == TRUE)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

int	is_export_syntax_error(char *cmd)
{
	return ((ft_strcmp(cmd, "") == TRUE) \
	|| (ft_isdigit(cmd[0]) == TRUE) \
	|| (is_in_charset(cmd[0], "`~!@#%$%^&*(){}\\|-\'\";:+,.=?/")) \
	|| (is_cmd_has_special_after_builtin(cmd)));
}

int	builtin_export(char **cmd, t_list *envl)
{
	int	idx;

	idx = 1;
	set_exit_code(g_global->g_envl, 0);
	if (cmd[1] == NULL || ft_strcmp(cmd[1], "_") == TRUE)
	{
		print_envl(envl);
		exit(0);
	}
	else
	{
		while (cmd[idx] != NULL)
		{
			if (is_export_syntax_error(cmd[idx]) == TRUE)
			{
				printf("AengMuShell $ export: `%s\': not a valid identifier\n", \
					cmd[idx++]);
				set_exit_code(g_global->g_envl, 1);
				continue ;
			}
			add_set_env_to_list(envl, cmd[idx++]);
		}
	}
	sort_envl(envl);
	return (1);
}
