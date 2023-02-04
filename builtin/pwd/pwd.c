/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:13:21 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/04 12:02:23 by hyungseok        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 1024);
	ft_putstr(cwd);
	ft_putstr("\n");
	free(cwd);
	exit(0);
}
