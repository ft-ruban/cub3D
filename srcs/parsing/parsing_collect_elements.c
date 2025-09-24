/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_collect_elements.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:27:19 by ldevoude          #+#    #+#             */
/*   Updated: 2025/09/24 15:55:54 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// if we are here it mean
// we found a letter that signal that an element is on the line
// we read a char and go to the right case between texture
// or rgb value.

static bool	element_found(int fd_sd, t_settings *set, char first_letter,
		char *read_buff)
{
	if (read(fd_sd, read_buff, 1) == -1)
		return (error_handler(set, INV_READ, "parsing_collect_elements.c:23 ",
				MSG_6));
	if (first_letter == 'N' || first_letter == 'S' || first_letter == 'W'
		|| first_letter == 'E')
	{
		if (is_texture_valid(fd_sd, set, first_letter, read_buff[0]))
			return (RETURN_FAILURE);
	}
	else if (first_letter == 'F' || first_letter == 'C')
	{
		if (read_buff[0] != ' ' && ft_isnum((int)read_buff[0]))
			return (error_handler(set, INV_CON,
					"parsing_collect_elements.c:34 ", MSG_7));
		if ((first_letter == 'F' && set->floor_r == NONE_ASSIGNED)
			|| (first_letter == 'C' && set->ceil_r == NONE_ASSIGNED))
		{
			if (is_rgb_valid(fd_sd, set, first_letter, false))
				return (RETURN_FAILURE);
		}
		else
			return (error_handler(set, INV_CON,
					"parsing_collect_elements.c:43 ", MSG_7));
	}
	return (RETURN_SUCCESS);
}
// that function's goal is to check if there is a missing element's
// content in our set struct
// if nothing is missed then return false to make the loop stop
// else it send a true to make it continue

static bool	is_there_an_element_missing(t_settings *set)
{
	if (!set->rp_no || !set->rp_so || !set->rp_we || !set->rp_ea
		|| set->floor_r == NONE_ASSIGNED || set->floor_g == NONE_ASSIGNED
		|| set->floor_b == NONE_ASSIGNED || set->ceil_r == NONE_ASSIGNED
		|| set->ceil_g == NONE_ASSIGNED || set->ceil_b == NONE_ASSIGNED)
		return (true);
	else
		return (false);
}

// here while we dont have all of our non map element
// such as textures, and the rgb value of floor and celling
// we stay in the loop. This is checked by are_all_element_filled
// of course if there is any error during the loop
// it does exit but with an error
// it read char by char the content of the file.
// if we reach EOF too early we send an error.
// if a non element letter OR an empty line(\n) is found
// we send an error as well. It continue until we found an error
// or until we got all of our necessary elements.

static bool	collect_elements(int fd_sd, t_settings *set, char *read_buff)
{
	while (is_there_an_element_missing(set))
	{
		if (read(fd_sd, read_buff, 1) == -1)
			return (error_handler(set, INV_READ,
					"parsing_collect_elements.c:80 ", MSG_6));
		if (read_buff[0] == 'N' || read_buff[0] == 'S' || read_buff[0] == 'W'
			|| read_buff[0] == 'E' || read_buff[0] == 'F'
			|| read_buff[0] == 'C')
		{
			printf("??\n");
			if (element_found(fd_sd, set, read_buff[0], read_buff))
				return (RETURN_FAILURE);
		}
		else if (read_buff[0] != '\n')
			return (error_handler(set, INV_CON,
					"parsing_collect_elements.c:90 ", MSG_7));
	}
	return (RETURN_SUCCESS);
}

// here we open a given file by checking in
// the map folder.
// it return the fd that hold the return of our open.
// if no readable file with the right name found fd would be = to -1
// that should be checked by the calling function.

static int	open_file_give_fd(char *file)
{
	char	*path;
	int		fd;

	path = ft_strjoin(MAP_FOLDER_PATH, file);
	if (!path)
		return (OPEN_FAILED);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}

// we open the file that was sent + save it in ptr of fd.
// then we set up our buff to hold a char + a \0 that we
// do immdediatly once the task complete. 
// (to avoid conflict with utils functions)
// the buff would be mostly used here
// for holding the last read of 1 content from the file
// then we collect our elements before returning 0 if
// all those tasks are successful.

bool	prepare_collect_elements(char *cub_file, t_settings *set,
	int *fd_sd, char **read_buff)
{
	*fd_sd = open_file_give_fd(cub_file);
	if (*fd_sd == OPEN_FAILED)
		return (error_handler(set, INV_FAIL, "parsing_collect_elements.c:126 ",
				MSG_4));
	*read_buff = malloc(2);
	if (!*read_buff)
	{
		close(*fd_sd);
		return (error_handler(set, MAL_ERR_BUFF,
				"parsing_collect_elements.c:130 ", MSG_5));
	}
	(*read_buff)[1] = '\0';
	if (collect_elements(*fd_sd, set, *read_buff))
	{
		close(*fd_sd);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
