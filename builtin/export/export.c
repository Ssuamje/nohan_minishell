/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:26:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 23:54:24 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	is_export_syntax_error(char *cmd)
{
	return ((ft_strcmp(cmd, "") == TRUE) \
	|| (ft_isdigit(cmd[0]) == TRUE) \
	|| (is_cmd_has_special_after(cmd)));
}

void	builtin_export(char **cmd, t_list *envl)
{
	int	idx;

	idx = 1;
	if (cmd[1] == NULL)
	{
		print_envl(envl);
	}
	else
	{
		while (cmd[idx] != NULL)
		{
			if (is_export_syntax_error(cmd[idx]) == TRUE)
			{
				printf("🐤AengMuShell $ export: `%s\': not a valid identifier\n", \
					cmd[idx]);
				idx++;
				continue ;
			}
			add_set_env_to_list(envl, cmd[idx++]);
		}
	}
}
