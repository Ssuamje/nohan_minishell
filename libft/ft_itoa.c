/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:24:39 by sanan             #+#    #+#             */
/*   Updated: 2022/11/09 21:13:14 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long long	set_num(int n, int *sign)
{
	if (n < 0)
	{
		*sign = -1;
		return (-1 * (long long)n);
	}
	else
	{
		*sign = 1;
		return ((long long)n);
	}
}

static int	count_digit(long long num, int sign)
{
	int	i;

	if (num == 0)
		return (1);
	if (sign == -1)
		i = 1;
	else
		i = 0;
	while (num > 0)
	{
		i++;
		num /= 10;
	}
	return (i);
}

static void	put_num(char *result, long long num, int sign, int digit)
{
	int	idx;

	idx = digit - 1;
	result[idx + 1] = 0;
	if (num == 0)
	{
		result[0] = '0';
		return ;
	}
	if (sign == -1)
		result[0] = '-';
	while (num > 0)
	{
		result[idx] = num % 10 + '0';
		num /= 10;
		idx--;
	}
}

char	*ft_itoa(int n)
{
	int			sign;
	long long	num;
	char		*result;
	int			digit;

	num = set_num(n, &sign);
	digit = count_digit(num, sign);
	result = malloc(sizeof(char) * digit + 1);
	if (!result)
		return (0);
	put_num(result, num, sign, digit);
	return (result);
}
