/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:26:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/03 13:55:26 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

// #이 되는 경우가 있음.

int	is_export_syntax_error(char *cmd)
{
	return ((ft_strcmp(cmd, "") == TRUE) \
	|| (is_in_str(cmd[0], "~`!@#$%^&*()-+=\"\':;|\\}]{[.,<>?/")) == TRUE);
}

void	builtin_export(char **cmd, t_list *envl)
{
	int	idx;

	idx = 1;
	if (cmd[1] == NULL)
		return (print_envl(envl));
	else
	{
		if (is_export_syntax_error(cmd[1]) == TRUE)
		{
			printf("export: `%s\': not a valid identifier\n", cmd[idx]);
			return ;
		}
		while (cmd[idx] != NULL)
		{
			if (is_export_syntax_error(cmd[idx]) == TRUE)
				return ;
			add_set_env_to_list(envl, cmd[idx++]);
		}
	}
	exit(0);
}
