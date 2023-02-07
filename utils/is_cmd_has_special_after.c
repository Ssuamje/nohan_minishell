/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd_has_special_after.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:22:34 by sanan             #+#    #+#             */
/*   Updated: 2023/02/07 23:30:48 by sanan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	is_cmd_has_special_after(char *cmd)
{
	int	idx;

	idx = 0;
	while (cmd[idx] != '\0')
	{
		if (is_in_str(cmd[idx], "`~!#%^&*(){}\\ |\'\";") == TRUE)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}
