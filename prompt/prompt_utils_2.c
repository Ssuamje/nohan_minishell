/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:27:03 by sanan             #+#    #+#             */
/*   Updated: 2023/02/05 22:19:58 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/prompt.h"

void	sig_int_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		add_set_env_to_list(g_envl, "?=1");
	}
}

void	sig_quit_handler(__attribute__((unused))int signo)
{
}

void	init_sighandler(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
}
