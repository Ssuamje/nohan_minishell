/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:35:04 by hyungnoh          #+#    #+#             */
/*   Updated: 2023/02/09 15:40:38 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	interpret_cur_file(t_process *cur)
{
	char	*tmp;
	int		i;

	i = -1;
	while (cur->cmd[++i] != NULL)
	{
		if (ft_strncmp(cur->cmd[i], "~/", 2) == 0 \
		|| ft_strcmp(cur->cmd[i], "~"))
		{
			tmp = cur->cmd[i];
			cur->cmd[i] = ft_join_and_free(\
					get_value_by_key(g_global->g_envl, "HOME"), \
					ft_join_and_free(ft_strdup("/"), \
					ft_strdup(&(cur->cmd[i][2]))));
			free(tmp);
		}
	}
}

int	is_binary(char *cmd, char **path)
{
	int		i;
	char	*tmp_cmd;

	if (path == NULL)
		return (0);
	i = 0;
	while (cmd[i] != '\0')
		i++;
	i--;
	while (cmd[i] != '/')
		i--;
	i = i + 2;
	tmp_cmd = malloc(sizeof(char) * i);
	ft_strlcpy(tmp_cmd, cmd, (size_t)i);
	i = -1;
	while (path[++i])
	{
		if (ft_strcmp(path[i], tmp_cmd))
		{
			free(tmp_cmd);
			return (1);
		}
	}
	free(tmp_cmd);
	return (0);
}

int	print_message_and_exit(char *cmd, struct stat *sb, int *exit_code)
{
	char	*err_msg;

	if (ft_strchr(cmd, '/') && stat(cmd, sb) != 0)
	{
		err_msg = ft_strjoin("AengMuShell: ", cmd);
		perror(err_msg);
		free(err_msg);
		*exit_code = 127;
		return (TRUE);
	}
	else if ((ft_strchr(cmd, '/') && stat(cmd, sb) == 0) && \
			(S_IFMT & sb->st_mode) != S_IFREG)
	{
		ft_putstr_fd("AengMuShell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		*exit_code = 126;
		return (TRUE);
	}
	err_msg = ft_strjoin("AengMuShell: ", cmd);
	perror(err_msg);
	free(err_msg);
	*exit_code = 126;
	return (TRUE);
}

int	permission_check(char **cmd, char **path)
{
	int			mode;
	int			exit_code;
	struct stat	sb;

	mode = R_OK | W_OK | X_OK;
	if (stat(cmd[0], &sb) == 0 && cmd[0][0] == '/' && path == NULL)
		execve(cmd[0], cmd, NULL);
	if (((access(cmd[0], mode) == 0 && stat(cmd[0], &sb) == 0) && \
		((S_IFMT & sb.st_mode) == S_IFREG)) \
	|| (stat(cmd[0], &sb) == 0 && is_binary(cmd[0], path)))
		return (1);
	if (print_message_and_exit(cmd[0], &sb, &exit_code) == TRUE)
		exit(exit_code);
	print_message_and_exit(cmd[0], &sb, &exit_code);
	exit(exit_code);
}
