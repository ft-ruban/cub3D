/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:30:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/14 10:46:09 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "linux/limits.h"
#include "parsing.h"
#include "utils.h"

// read a single char, if EOF return error,
// if space we read until it is not a space in the buff anymore
// here we do a gnl to get the line that should have the right content
// if not it would be detected during the init of minilibx anyway


static bool	find_texture_element_path(int fd_sd, char **element,
		t_settings *set)
{
	char *element_buff;

	element_buff = NULL;
	if (read(fd_sd, set->buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_texture.c ", MSG_6));
	printf("buffintext = %c\n", set->buff[0]);
	while (set->buff[0] == ' ')
	{
		printf("buff =a %c\n", set->buff[0]);
		if (read(fd_sd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "parsing_texture.c ", MSG_6));
	}
	element_buff = get_next_line(fd_sd);
	if (!element_buff)
		return (error_handler(set, GNL_FAILED, "parsing_texture.c ", MSG_9)); //plutot malloc? ou special GNL jsp
	*element = ft_strjoin(set->buff, element_buff);
	if(!*element)
	{
		free(element_buff);
		return (error_handler(set, STRJOIN_FAILED, "parsing_texture.c ", MSG_10));
	}
	free(element_buff);
	return (RETURN_SUCCESS);
}
// if fail here it mean we already got the information
// so invalid file's content. Else we go to find the path
// to fill the ptr that point to the right variable in oru struct

bool	is_texture_valid(int fd_sd, t_settings *set, char first_letter,
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
