/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:03:19 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/prompt.h"
#define WAIT_FOR_SIG 1

void	parse_and_execute(char *input)
{
	t_list	*processes;
	char	**tmp_envp;

	processes = parse(g_global->g_envl, input);
	if (processes != NULL)
	{
		tmp_envp = envl_to_envp(g_global->g_envl);
		exec_process(tmp_envp, processes);
		free_process_list(processes);
		free_split(tmp_envp);
	}
}

t_global	*init_global(char **envp)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (global == NULL)
		exit_error(ERR_MALLOC);
	global->g_envl = map_envp_to_list(envp);
	global->g_sigint_flag = FALSE;
	return (global);
}

void	free_global(t_global **global)
{
	t_list		*tmp;
	t_environ	*tmp_env;

	tmp = (*global)->g_envl->next;
	while (tmp != NULL)
	{
		tmp_env = tmp->content;
		free(tmp_env->key);
		free(tmp_env->value);
		tmp = tmp->next;
	}
	ft_lstclear(&((*global)->g_envl), free);
	free(*global);
}

int	main(int ac, __attribute__((unused))char **av, char **envp)
{
	char	*input;
	int		exit_code;

	if (ac != 1)
		exit_error(ERR_ARGC);
	print_logo();
	init_sighandler();
	g_global = init_global(envp);
	while (WAIT_FOR_SIG)
	{
		input = readline("🐤AengMuShell$ ");
		if (input == NULL)
		{
			printf("exit\n");
			exit_code = convert_question_value_and_free(\
					get_value_by_key(g_global->g_envl, "?"));
			free_global(&g_global);
			return (exit_code);
		}
		add_history(input);
		if (is_input_empty(input) == TRUE)
			continue ;
		parse_and_execute(input);
		free(input);
	}
}
