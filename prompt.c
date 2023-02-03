/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/02/03 13:07:24 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/prompt.h"
#define WAIT_FOR_SIG 1

//need to delete
#include <unistd.h>
void check_leaks(void)
{
	char *str = "\n**********************PROGRAM END************************\n";
	write(1, str, ft_strlen(str));
	system("leaks minishell");
}

int	main(int ac, __attribute__((unused))char **av, char **envp)
{
	char	*input;
	t_list	*processes;

	if (ac != 1)
		exit_error(ERR_ARGC);
	signal(SIGINT, sighandler);
	g_envl = map_envp_to_list(envp);
	while (WAIT_FOR_SIG)
	{
		input = readline("🐤AengMuShell $ ");
		if (input == NULL)
			return (1);
		add_history(input);
		if (is_input_empty(input) == TRUE)
			continue ;
		processes = parse(g_envl, input);
		if (processes != NULL)
		{
			print_processes_list(processes);
			builtin_unset(((t_process *)processes->next->content)->cmd, g_envl);
			print_envl(g_envl);
			// exec_process(envp, processes);
			free_process_list(processes);
		}
		free(input);
	}
}
