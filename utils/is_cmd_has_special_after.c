/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd_has_special_after.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungnoh <hyungnoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:22:34 by sanan             #+#    #+#             */
/*   Updated: 2023/02/03 18:56:05 by hyungnoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	is_cmd_has_special_after(char *cmd)
{
	int idx;
	
	idx = 0;
	while (cmd[idx] != '\0')
	{
		if (is_in_str(cmd[idx], "~`!@#$%^&*()-+\"\':;|\\}]{[.,<>?/") == TRUE)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}