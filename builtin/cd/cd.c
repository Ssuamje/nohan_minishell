/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:27:25 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/05 14:08:16 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	set_env_pwd(char *dir)
{
	char	*tmp_oldpwd;

	tmp_oldpwd = get_value_by_key(g_envl, "OLDPWD");
	add_set_env_to_list(g_envl, ft_join_and_free(ft_strdup("OLDPWD="), \
							get_value_by_key(g_envl, "PWD")));
	if (ft_strcmp(dir, "..") == TRUE)
	{
		add_set_env_to_list(g_envl, ft_join_and_free(ft_strdup("PWD="), \
									tmp_oldpwd));
	}
	else if (ft_strcmp(dir, "~") == TRUE)
	{
		add_set_env_to_list(g_envl, ft_join_and_free(ft_strdup("PWD="), \
									get_value_by_key(g_envl, "ZDOTDIR")));
		free(tmp_oldpwd);
	}
	else
	{
		add_set_env_to_list(g_envl, ft_join_and_free(ft_strdup("PWD="), \
									ft_strdup(dir)));
		free(tmp_oldpwd);
	}
}

void	builtin_cd(t_process *cur)
{
	if (cur->cmd[1] == NULL || ft_strcmp(cur->cmd[1], "~"))
	{
		if (find_env_by_key(g_envl, "HOME") == NULL)
		{
			printf("cd: HOME not set\n");
			return(set_exit_code(g_envl, 1));
		}
		else
			chdir(getenv("HOME"));
	}
	else
	{

		if (chdir(cur->cmd[1]) == -1)	
		{
			printf("cd: %s: No such file or directory\n", cur->cmd[1]);
			set_exit_code(g_envl, 1);
		}
	}
	set_env_pwd(cur->cmd[1]);
}
