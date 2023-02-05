/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:00:08 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 19:25:31 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/prompt.h"
#define WAIT_FOR_SIG 1

//need to delete
#include <unistd.h>
void	check_leaks(void)
{
	char *str = "\n**********************PROGRAM END************************\n";
	write(1, str, ft_strlen(str));
	system("leaks minishell");
}

int	main(int ac, __attribute__((unused))char **av, char **envp)
{
	char	*input;
	t_list	*processes;
	char	**tmp_envp;

	// atexit(check_leaks);
	if (ac != 1)
		exit_error(ERR_ARGC);
	// rl_catch_signals = 0; (시그널 프롬프트에 안 뜨게 값 수정, 기본 값은 1)
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
			tmp_envp = envl_to_envp(g_envl);
			exec_process(tmp_envp, processes);
			free_process_list(processes);
			free_split(tmp_envp);
		}
		free(input);
	}
}
