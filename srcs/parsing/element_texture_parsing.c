/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_texture_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:30:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/08 16:16:31 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// read a single char, if EOF return error,
// if space we read until it is not a space in the buff anymore
// here we do a gnl to get the line that should have the right content
// if not it would be detected during the init of minilibx anyway

static bool	find_texture_element_path(int fd_sd, char **element,
		t_parsing *parsing)
{
	char	*element_buff;

	element_buff = NULL;
	if (read(fd_sd, parsing->buff, 1) == -1)
		return (error_handler(parsing, INV_READ, "parsing_texture.c:27 ", MSG_6));
	while (parsing->buff[0] == ' ')
	{
		if (read(fd_sd, parsing->buff, 1) == -1)
			return (error_handler(parsing, INV_READ, "parsing_texture.c:31 ",
					MSG_6));
	}
	element_buff = get_next_line(fd_sd);
	if (!element_buff)
		return (error_handler(parsing, GNL_FAILED, "parsing_texture.c:35 ", MSG_9));
	*element = ft_strjoin(parsing->buff, element_buff);
	if (!*element)
	{
		free(element_buff);
		return (error_handler(parsing, STRJOIN_FAILED, "parsing_texture.c:38 ",
				MSG_10));
	}
	free(element_buff);
	return (RETURN_SUCCESS);
}
// if fail here it mean we already got the information
// so invalid file's content. Else we go to find the path
// to fill the ptr that point to the right variable in oru struct

bool	is_texture_valid(int fd_sd, t_parsing *parsing, char first_letter,
		char second_letter)
{
	if (first_letter == 'N')
	{
		if (parsing->rp_no || second_letter != 'O')
			return (error_handler(parsing, INV_CON, FILE_ERR_2, MSG_7));
		return (find_texture_element_path(fd_sd, &parsing->rp_no, parsing));
	}
	else if (first_letter == 'S')
	{
		if (parsing->rp_so || second_letter != 'O')
			return (error_handler(parsing, INV_CON, FILE_ERR_3, MSG_7));
		return (find_texture_element_path(fd_sd, &parsing->rp_so, parsing));
	}
	else if (first_letter == 'W')
	{
		if (parsing->rp_we || second_letter != 'E')
			return (error_handler(parsing, INV_CON, FILE_ERR_4, MSG_7));
		return (find_texture_element_path(fd_sd, &parsing->rp_we, parsing));
	}
	else if (first_letter == 'E')
	{
		if (parsing->rp_ea || second_letter != 'A')
			return (error_handler(parsing, INV_CON, FILE_ERR_5, MSG_7));
		return (find_texture_element_path(fd_sd, &parsing->rp_ea, parsing));
	}
	return (RETURN_FAILURE);
}
