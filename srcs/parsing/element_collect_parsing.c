/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_collect_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:27:19 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/12 13:13:08 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// if we are here it mean
// we found a letter that signal that an element is on the line
// we read a char and go to the right case between texture
// or rgb value.

// TODO warning new version that is untested yet

static bool	element_found(int fd_sd, t_cub3d *cub3d, char first_letter,
		int element_type)
{
	if (read(fd_sd, cub3d->parsing->buff, 1) == -1)
		return (error_handler(cub3d, INV_READ, "parsing_collect_elements.c:23 ",
				MSG_6));
	else if (element_type == TYPE_TEXTURE)
	{
		if (is_texture_valid(fd_sd, cub3d, first_letter, cub3d->parsing->buff[0]))
			return (RETURN_FAILURE);
	}
	else if (element_type == TYPE_RGB)
	{
		if (cub3d->parsing->buff[0] != ' ' && ft_isnum((int)cub3d->parsing->buff[0]))
			return (error_handler(cub3d, INV_CON,
					"parsing_collect_elements.c:34 ", MSG_7));
		else if (is_rgb_valid(fd_sd, cub3d, first_letter, false))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

// here while we dont have all of our non map element
// such as textures, and the rgb value of floor and celling
// we stay in the loop. This is checked by are_all_element_filled
// of course if there is any error during the loop
// it does exit but with an error
// it read char by char the content of the file.
// if we reach EOF too early we send an error.
// if a non element letter OR  empty line(\n) is found
// we send an error as well. It continue until we found an error
// or until we got all of our necessary elements.

static bool	browse_to_find_elements(int fd_sd,t_cub3d *cub3d, t_parsing *parsing, char *read_buff)
{
	int	element_type;

	element_type = NONE_ASSIGNED;
	while (an_element_is_missing(parsing))
	{
		if (read(fd_sd, read_buff, 1) == -1)
			return (error_handler(cub3d, INV_READ,
					"parsing_collect_elements.c:80 ", MSG_6));
		element_type = which_element_type(read_buff[0], parsing);
		if (element_type == TYPE_RGB || element_type == TYPE_TEXTURE)
		{
			if (element_found(fd_sd, cub3d, read_buff[0], element_type))
				return (RETURN_FAILURE);
		}
		else if (element_type != TYPE_EMPTY_LINE)
			return (error_handler(cub3d, INV_CON,
					"parsing_collect_elements.c:90 ", MSG_7));
	}
	return (RETURN_SUCCESS);
}

// we open the file that was sent by user + save it in ptr of fd.
// then we set up our buff to hold a char + a \0 that we
// do immdediatly once the task complete.
// (to avoid conflict with utils functions)
// the buff would be mostly used here
// for holding the last read of 1 content from the file
// then we collect our elements before returning 0 if
// all those tasks are successful.

// TODO? rename cub_file en sd_file

bool	prepare_collect_elements(char *cub_file, t_cub3d *cub3d, int *fd_sd,
		char **read_buff)
{
	*fd_sd = open_sd_file_give_fd(cub_file);
	if (*fd_sd == OPEN_FAILED)
		return (error_handler(cub3d, INV_FAIL, "parsing_collect_elements.c:126 ",
				MSG_4));
	*read_buff = malloc(2);
	if (!*read_buff)
	{
		close(*fd_sd);
		return (error_handler(cub3d, MAL_ERR_BUFF,
				"parsing_collect_elements.c:130 ", MSG_5));
	}
	(*read_buff)[1] = '\0';
	if (browse_to_find_elements(*fd_sd, cub3d, cub3d->parsing, *read_buff))
	{
		close(*fd_sd);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
