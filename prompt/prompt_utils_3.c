/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:12:27 by sanan             #+#    #+#             */
/*   Updated: 2023/02/09 14:43:24 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/prompt.h"

void	sigint_default(int signo)
{
	if (signo == SIGINT)
		printf("\n");
}

void	set_sigint_to_default(void)
{
	signal(SIGINT, sigint_default);
	signal(SIGQUIT, SIG_DFL);
}
