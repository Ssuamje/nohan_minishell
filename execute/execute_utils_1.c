/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:38:33 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:32:52 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

char	*find_full_path(t_process *cur, char **path, int *flag)
{
	char		*tmp_path;
	struct stat	sb;
	int			i;

	i = 0;
	if (stat(cur->cmd[0], &sb) == 0)
	{
		tmp_path = ft_strdup(cur->cmd[0]);
		*flag = ABSOLUTE;
		return (tmp_path);
	}
	while (path[++i])
	{
		tmp_path = ft_strjoin(path[i], cur->cmd[0]);
		if (stat(tmp_path, &sb) == 0)
			return (tmp_path);
		free(tmp_path);
	}
	return (NULL);
}

int	check_cmd(t_process *cur, char **path, int i)
{
	char		*tmp_path;
	struct stat	sb;

	if (cur->cmd[0] == NULL)
		return (2);
	if (ft_strcmp("..", cur->cmd[0]) || ft_strcmp("''", cur->cmd[0]) \
	|| ft_strcmp("""", cur->cmd[0]))
		return (0);
	if ((ft_strchr(cur->cmd[0], '/') && permission_check(cur->cmd, path)) \
	|| path == NULL)
		return (1);
	while (path[++i])
	{
		tmp_path = ft_strjoin(path[i], cur->cmd[0]);
		if (stat(tmp_path, &sb) == 0)
		{
			free(tmp_path);
			return (1);
		}
		free(tmp_path);
	}
	if (ft_strcmp(cur->cmd[0], "echo") || ft_strcmp(cur->cmd[0], "pwd") \
	|| (ft_strcmp(cur->cmd[0], "export") && cur->cmd[1] == NULL))
		return (1);
	return (0);
}

void	manage_pipe(t_process *cur, t_process *next, char **path, pid_t pid)
{
	if (pid == CHILD)
	{
		close(cur->pfd[0]);
		if (next != NULL && check_cmd(cur, path, 0) == 1)
			dup2(cur->pfd[1], STDOUT_FILENO);
		close(cur->pfd[1]);
	}
	else if (pid > 0)
	{
		close(cur->pfd[1]);
		dup2(cur->pfd[0], STDIN_FILENO);
		close(cur->pfd[0]);
	}
}

int	find_last_slash_index(char *cmd)
{
	int	idx;

	idx = 0;
	if (cmd == NULL)
		return (-1);
	while (cmd[idx])
		idx++;
	idx--;
	while (idx >= 0)
	{
		if (cmd[idx] == '/')
			return (idx);
		idx--;
	}
	return (-1);
}

void	parse_cmd(t_process *cur)
{
	char	*tmp;
	int		idx_slash;

	idx_slash = find_last_slash_index(cur->cmd[0]);
	if (idx_slash == -1)
		return ;
	tmp = ft_strdup(&(cur->cmd[0][idx_slash + 1]));
	free(cur->cmd[0]);
	cur->cmd[0] = tmp;
}
