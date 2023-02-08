/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:13:21 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/08 09:58:54 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 1024);
	if (cwd == NULL)
		exit(1);
	ft_putstr(cwd);
	ft_putstr("\n");
	free(cwd);
	exit(0);
}
