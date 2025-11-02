/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:00:20 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 14:00:25 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	character_is_invalid(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != '\0' && c != '\n' && c != ' ')
		return (RETURN_FAILURE);
	else
		return (RETURN_SUCCESS);
}

bool	player_update_check(bool *player)
{
	if (*player == true)
		return (RETURN_FAILURE);
	else
		*player = true;
	return (RETURN_SUCCESS);
}
