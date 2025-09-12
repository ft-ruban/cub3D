/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:26:09 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/12 14:57:34 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "linux/limits.h"
#include "parsing.h"
#include <stdbool.h> //bool duh
#include <stdio.h>   //printf TORM

static int	element_found(int fd_sd, t_settings *set, char first_letter,
		char *buff)
{
	if (read(fd_sd, buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_rgb.c:9 ", MSG_6));
	if (first_letter == 'N' || first_letter == 'S' || first_letter == 'W'
		|| first_letter == 'E')
	{
		if (is_texture_valid(fd_sd, set, first_letter, buff[0]))
			return (RETURN_FAILURE);
	}
	else if (first_letter == 'F' || first_letter == 'C')
	{
		if ((first_letter == 'F' && set->floor_r == -1) || (first_letter == 'C'
				&& set->cell_r == -1))
		{
			if (rgb_thing(fd_sd, set, first_letter, false))
				return (RETURN_FAILURE);
		}
		else
			return (error_handler(set, INV_CON, "parsing_elements.c:", MSG_7));
	}
	return (RETURN_SUCCESS);
}
// that function's goal is to check if all our settings are assigned.
// to exit the loop at collect_elements. the loop is supposed to continue
// until everything got filled

static int	are_all_elements_filled(t_settings *set)
{
	if (!set->rp_no || !set->rp_so || !set->rp_we || !set->rp_ea
		|| set->floor_r == NONE_ASSIGNED || set->floor_g == NONE_ASSIGNED
		|| set->floor_b == NONE_ASSIGNED || set->cell_r == NONE_ASSIGNED
		|| set->cell_g == NONE_ASSIGNED || set->cell_b == NONE_ASSIGNED)
		return (RETURN_FAILURE);
	else
		return (RETURN_SUCCESS);
}

// TODO lot of error case, need a function to warn the user with the
// proper message + free potential things like buff for ex

int	collect_elements(int fd_sd, t_settings *set)
{
	while (are_all_elements_filled(set))
	{
		if (read(fd_sd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "parsing_elements.c:51",
					MSG_6));
		if (set->buff[0] == 'N' || set->buff[0] == 'S' || set->buff[0] == 'W'
			|| set->buff[0] == 'E' || set->buff[0] == 'F'
			|| set->buff[0] == 'C')
		{
			if (element_found(fd_sd, set, set->buff[0], set->buff))
				return (error_handler(set, INV_CON, "parsing_element.c",
						MSG_7));
		}
		else if (set->buff[0] != '\n')
			return (error_handler(set, INV_CON, "parsing_element.c", MSG_7));
	}
	return (RETURN_SUCCESS);
}
