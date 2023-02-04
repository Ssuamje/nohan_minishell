/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/02/04 14:30:54 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/prompt.h"
#define WAIT_FOR_SIG 1

//need to delete
#include <unistd.h>
void check_leaks(void)
{
	char *str = "\n**********************PROGRAM END************************\n";
	write(1, str, ft_strlen(str));
	system("leaks a.out");
}

int	main(int ac, __attribute__((unused))char **av, char **envp)
{
	char	*input;
	t_list	*processes;
	char	**tmp_envp;

	if (ac != 1)
		exit_error(ERR_ARGC);
	signal(SIGINT, sighandler);
	g_envl = map_envp_to_list(envp);
	atexit(check_leaks);
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
			tmp_envp = envl_to_envp(g_envl);
			// print_processes_list(processes);
			// print_envl(g_envl);
			exec_process(tmp_envp, processes);
			free_process_list(processes);
			free_split(tmp_envp);
		}
		free(input);
	}
}
