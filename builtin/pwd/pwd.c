/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:13:21 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/09 11:10:57 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 1024);
	if (cwd == NULL)
	{
		cwd = get_value_by_key(g_global->g_envl, "PWD");
		printf("%s\n", cwd);
		free(cwd);
		exit(0);
	}
	ft_putstr(cwd);
	ft_putstr("\n");
	free(cwd);
	exit(0);
}
