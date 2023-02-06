/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:27:25 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/06 19:55:39 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#define SUCCESS 0
#define HOME_NOT_SET 1
#define NO_FILE_DIR 2

void	set_env_pwd(void)
{
	char	*to_put;

	to_put = ft_join_and_free(ft_strdup("OLDPWD="), \
								get_value_by_key(g_global->g_envl, "PWD"));
	add_set_env_to_list(g_global->g_envl, to_put);
	free(to_put);
	to_put = ft_join_and_free(ft_strdup("PWD="), getcwd(NULL, 1024));
	add_set_env_to_list(g_global->g_envl, to_put);
	free(to_put);
}

int	print_set_exit_code(int error_flag, int exit_code, int flag, char *dir)
{
	if (error_flag == HOME_NOT_SET)
		printf("AengMuShell: cd: HOME not set\n");
	if (error_flag == NO_FILE_DIR)
		printf("AengMuShell: cd: %s: No such file or directory\n", dir);
	set_exit_code(g_global->g_envl, exit_code);
	if (flag == TRUE)
		free(dir);
	return (1);
}

void	set_dir_home_set_flag_chdir(char **dir, int *flag)
{
	*dir = get_value_by_key(g_global->g_envl, "HOME");
	*flag = TRUE;
	chdir(*dir);
}

void	interpret_home_set_dir_flag(t_process *cur, char **dir, int *flag)
{
	*dir = ft_join_and_free(get_value_by_key(g_global->g_envl, "HOME"), \
				ft_join_and_free(ft_strdup("/"), ft_strdup(&(cur->cmd[1][2]))));
	*flag = TRUE;
}

int	builtin_cd(t_process *cur)
{
	char	*dir;
	int		flag;

	dir = cur->cmd[1];
	flag = FALSE;
	if (dir == NULL || ft_strcmp(dir, "~") == TRUE)
	{
		if (find_env_by_key(g_global->g_envl, "HOME") == NULL)
			return (print_set_exit_code(HOME_NOT_SET, 1, flag, NULL));
		else
			set_dir_home_set_flag_chdir(&dir, &flag);
	}
	else
	{
		if (ft_strncmp(dir, "~/", 2) == 0)
			interpret_home_set_dir_flag(cur, &dir, &flag);
		if (chdir(dir) == -1)
			return (print_set_exit_code(NO_FILE_DIR, 1, flag, dir));
	}
	print_set_exit_code(SUCCESS, 0, flag, dir);
	set_env_pwd();
	return (1);
}
