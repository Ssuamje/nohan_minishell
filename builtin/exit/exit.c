/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:45:25 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 20:57:22 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

int	is_arg_numeric(char *arg)
{
	int idx;

	idx = 0;
	if (arg[0] == '-')
	{
		idx++;
		while (arg[idx] != '\0')
		{
			if (ft_isdigit(arg[idx]) == FALSE)
				return (FALSE);
			idx++;
		}
		return (TRUE);
	}
	while (arg[idx] != '\0')
	{
		if (ft_isdigit(arg[idx]) == FALSE)
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

int	is_exit_syntax_error(char **args)
{
	if (is_arg_numeric(args[1]) == FALSE)
	{
		printf("🐤AengMuShell $ exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (args[2] != NULL)
	{
		printf("🐤AengMuShell $ exit: too many arguments\n");
		exit(1);
	}
	return (FALSE);
}

int	convert_question_value_and_free(char *value)
{
	int	exit_code;

	exit_code = ft_atoi(value);
	free(value);
	return (exit_code);
}

int	minus_char_max_absolute(int n)
{
	int	num;

	num = n % 256;

	if (num < 0)
		return (256 + num);
	else
		return (256 - num);
}

void	builtin_exit(char **cmd, t_list *envl)
{
	int	former_exit_code;

	if (is_exit_syntax_error(cmd) == TRUE)
		;
	if (is_arg_numeric(cmd[1]) == TRUE)
		exit(minus_char_max_absolute(
					ft_atoi(cmd[1])));
	if (cmd[1] == NULL)
	{
		former_exit_code = convert_question_value_and_free(
							get_value_by_key(envl, "?"));
		exit(former_exit_code);
	}
}