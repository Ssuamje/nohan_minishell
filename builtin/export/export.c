/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:26:02 by sanan             #+#    #+#             */
/*   Updated: 2023/02/03 12:14:26 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	is_in_str(char c, char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == c)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}

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
}
