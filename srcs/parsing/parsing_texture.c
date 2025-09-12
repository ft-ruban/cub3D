/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:30:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/12 14:31:42 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "linux/limits.h"
#include "parsing.h"
#include "utils.h"

static int	find_texture_element_path(int fd_sd, char **element,
		t_settings *set)
{
	if (read(fd_sd, set->buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_texture.c ", MSG_6));
	while (set->buff[0] == ' ')
	{
		if (read(fd_sd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "parsing_texture.c ", MSG_6));
	}
	*element = get_next_line(fd_sd);
	if (!*element)
		return (error_handler(set, INV_READ, "parsing_texture.c ", MSG_6));
	return (RETURN_SUCCESS);
}
// if fail here it mean we already got the information
//(let's assume we DO NOT accept duplicates to not make things more confusing)
// TODO create an utils function that would setup 
// an error type and return failure to avoid repetition

int	is_texture_valid(int fd_sd, t_settings *set, char first_letter,
		char second_letter)
{
	if (first_letter == 'N')
	{
		if (set->rp_no || second_letter != 'O')
			return (error_handler(set, INV_CON, "parsing_texture.c: ", MSG_7));
		return (find_texture_element_path(fd_sd, &set->rp_no, set));
	}
	else if (first_letter == 'S')
	{
		if (set->rp_so || second_letter != 'O')
			return (error_handler(set, INV_CON, "parsing_texture.c: ", MSG_7));
		return (find_texture_element_path(fd_sd, &set->rp_so, set));
	}
	else if (first_letter == 'W')
	{
		if (set->rp_we || second_letter != 'E')
			return (error_handler(set, INV_CON, "parsing_texture.c: ", MSG_7));
		return (find_texture_element_path(fd_sd, &set->rp_we, set));
	}
	else if (first_letter == 'E')
	{
		if (set->rp_ea || second_letter != 'A')
			return (error_handler(set, INV_CON, "parsing_texture.c ", MSG_7));
		return (find_texture_element_path(fd_sd, &set->rp_ea, set));
	}
	return (RETURN_FAILURE);
}
