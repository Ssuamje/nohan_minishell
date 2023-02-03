/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungseok <hyungseok@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/02/03 22:31:39 by hyungseok        ###   ########.fr       */
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
	char	**my_envp;

	if (ac != 1)
		exit_error(ERR_ARGC);
	signal(SIGINT, sighandler);
	g_envl = map_envp_to_list(envp);
	my_envp = envl_to_envp(g_envl);
	// print_split(my_envp);
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
			// print_envl(g_envl);
			my_envp = envl_to_envp(g_envl);
			exec_process(my_envp, processes);
			free_process_list(processes);
			free_split(my_envp);
		}
		free(input);
	}
}
