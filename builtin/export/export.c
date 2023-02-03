/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:26:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/03 16:16:49 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	is_cmd_has_special_after(char *cmd)
{
	int idx;
	
	idx = 0;
	while (cmd[idx] != '\0')
	{
		if (is_in_str(cmd[idx], "~`!@#$%^&*()-+=\"\':;|\\}]{[.,<>?/") == TRUE)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

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
		return (print_envl(envl));
	else
	{
		while (cmd[idx] != NULL)
		{
			if (is_export_syntax_error(cmd[idx]) == TRUE)
			{
				printf("export: `%s\': not a valid identifier\n", cmd[idx]);
				return ;
			}
			add_set_env_to_list(envl, cmd[idx++]);
		}
	}
}
