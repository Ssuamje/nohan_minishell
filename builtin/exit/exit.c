/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:45:25 by sanan             #+#    #+#             */
/*   Updated: 2023/02/03 19:33:17 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

//9223372036854775807, -9,223,372,036,854,775,808 오버플로우인 경우 numeric 에러처리
//처음 숫자, 이후에 인자가 올 경우 exit: too many arguments
//exit: a: numeric argument required
//롱롱 범위 안에서는 오버플로우가 계속 일어나고 있음.

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

int	set_up_down_long_long_max(char *arg, int sign, int *up_down)
{
	int idx;
	char *long_long_max_plus;
	char *long_long_max_minus;

	idx = 0;
	long_long_max_plus = "9223372036854775807";
	long_long_max_minus = "9223372036854775808";
	if (sign == -1)
	{
		while (idx < 19)
		{
			if (arg[idx] >= long_long_max_minus[idx])
				up_down[idx] = 1;
			idx++;
		} 
		if (idx == 19 && arg[18] > '8')
			return (TRUE);
	}
	else
	{
		while (idx < 19)
		{
			if (arg[idx] >= long_long_max_plus[idx])
				up_down[idx] = 1;
			idx++;
		}
		if (idx == 19 && arg[18] > '7')
			return (TRUE);
	}
	return (FALSE);
}

int	is_arg_long_long_overflow(char *arg)
{
	int	len_arg;
	int	up_down[19];

	len_arg = ft_strlen(arg);
	if (len_arg < 19)
		return (FALSE);
	if (len_arg > 20)
		return (TRUE);
	if (arg[0] == '-')
		return (set_up_down_long_long_max(arg, -1, up_down));
	else
		return (set_up_down_long_long_max(arg, 1, up_down));
}

int	is_exit_syntax_error(char **args)
{
	if ((is_arg_numeric(args[1]) == FALSE)
	|| (is_arg_long_long_overflow(args[1]) == TRUE))
	{
		printf("exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (args[2] != NULL)
	{
		printf("exit: too many arguments\n");
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
	printf("nothing error\n");
	if (is_arg_numeric(cmd[1]) == TRUE)
		exit(minus_char_max_absolute(
					ft_atoi(cmd[1])));
	printf("nothing error\n");
	if (cmd[1] == NULL)
	{
		former_exit_code = convert_question_value_and_free(
							get_value_by_key(envl, "?"));
		exit(former_exit_code);
	}
}