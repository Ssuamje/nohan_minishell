/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/02/06 19:46:08 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/prompt.h"
#define WAIT_FOR_SIG 1

void	parse_and_execute(char *input)
{
	t_list	*processes;
	char	**tmp_envp;

	processes = parse(g_envl, input);
	if (processes != NULL)
	{
		tmp_envp = envl_to_envp(g_envl);
		exec_process(tmp_envp, processes);
		free_process_list(processes);
		free_split(tmp_envp);
	}
}

int	main(int ac, __attribute__((unused))char **av, char **envp)
{
	char	*input;

	if (ac != 1)
		exit_error(ERR_ARGC);
	print_logo();
	init_sighandler();
	g_envl = map_envp_to_list(envp);
	while (WAIT_FOR_SIG)
	{
		input = readline("🐤AengMuShell$ ");
		if (input == NULL)
		{
			printf("exit\n");
			return (0);
		}
		add_history(input);
		if (is_input_empty(input) == TRUE)
			continue ;
		parse_and_execute(input);
		free(input);
	}
}
