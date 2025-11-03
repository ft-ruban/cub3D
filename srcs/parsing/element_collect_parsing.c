/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_collect_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:27:19 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/03 19:46:22 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// 1) An element has been found, we read one char in advance and depending of
//    which element we are dealing with (texture_path OR rgb value) we redirect
//    properly

static bool	element_found(int fd_sd, t_cub3d *cub3d, char first_letter,
		int element_type)
{
	if (read(fd_sd, cub3d->parsing->buff, 1) == -1)
		return (error_handler(cub3d, ELEMENT_MISS,
				"(element_collect_parsing.c:22) ", MSG_6));
	else if (element_type == TYPE_TEXTURE)
	{
		if (is_texture_valid(fd_sd, cub3d, first_letter,
				cub3d->parsing->buff[0]))
			return (RETURN_FAILURE);
	}
	else if (element_type == TYPE_RGB)
	{
		if (cub3d->parsing->buff[0] != ' '
			&& ft_isnum((int)cub3d->parsing->buff[0]))
			return (error_handler(cub3d, INV_CON_RGB,
					"(element_collect_parsing.c:33) ", MSG_7));
		else if (is_rgb_valid(fd_sd, cub3d, first_letter, false))
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

// 1) This is the loop that will continue until we found all the right elements
//    (in any order as long the file is valid) it will stop and send error
//	  if those elements are impossible to found or if there is unauthorized
//    types or any other kind of error that could happen during the process.
//    empty lines are ok as long they are empties.
//    (a line that hold a space is not considered as empty Per se)

static bool	browse_to_find_elements(int fd_sd, t_cub3d *cub3d,
		t_parsing *parsing, char *read_buff)
{
	int	element_type;
	int	res_read;

	element_type = NONE_ASSIGNED;
	while (an_element_is_missing(parsing))
	{
		res_read = read(fd_sd, read_buff, 1);
		if (res_read == 0 || res_read == -1)
			return (error_handler(cub3d, ELEMENT_MISS,
					"(element_collect_parsing.c:60) ", MSG_6));
		element_type = which_element_type(read_buff[0], parsing);
		if (element_type == TYPE_RGB || element_type == TYPE_TEXTURE)
		{
			if (element_found(fd_sd, cub3d, read_buff[0], element_type))
				return (RETURN_FAILURE);
		}
		else if (element_type != TYPE_EMPTY_LINE)
			return (error_handler(cub3d, INV_CON_ELE,
					"(element_collect_parsing.c:69) ", MSG_7));
	}
	return (RETURN_SUCCESS);
}

// 1) we open the file that was sent by user + save it as a file descriptor
// 2) we set up our buff to hold a char + a \0 to avoid conflict with some utils
//    functions the buffer is used to read through the file to collect the datas
// 3) Now that all is well set we start to browse the content of file to find
//    our elements

bool	prepare_collect_elements(char *cub_file, t_cub3d *cub3d, int *fd_sd,
		char **read_buff)
{
	*fd_sd = open_sd_file_give_fd(cub_file);
	if (*fd_sd == OPEN_FAILED)
		return (error_handler(cub3d, OPEN_FD_ELE,
				"(element_collect_parsing.c:86) ", MSG_4));
	*read_buff = malloc(2);
	if (!*read_buff)
	{
		close(*fd_sd);
		return (error_handler(cub3d, MAL_ERR_BUFF,
				"(element_collect_parsing.c:90) ", MSG_5));
	}
	(*read_buff)[1] = '\0';
	if (browse_to_find_elements(*fd_sd, cub3d, cub3d->parsing, *read_buff))
	{
		close(*fd_sd);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
