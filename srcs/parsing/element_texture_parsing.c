/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_texture_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:30:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 16:39:22 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// 1) Util function used to remove any potential \n(new_line char) from the
//    string

static char	*new_line_remover(char *element)
{
	char	*str;
	int		len_string;

	len_string = ft_strlen(element);
	if (len_string == 0)
	{
		free(element);
		return (NULL);
	}
	if (element[len_string - 1] == '\n')
	{
		element[len_string - 1] = '\0';
		str = ft_strdup(element);
		if (!str)
		{
			free(element);
			return (NULL);
		}
	}
	else
		str = element;
	free(element);
	return (str);
}

// 1) check if there is any space char between the path and the element type.
//    we ignore them all until we reach a char that is not a space.
// 2) gnl to retrieve the path that was given in the file in param
// 3) remove the '\n'(new line char) from the string of char to get an usable
//    path then leave once it is done.

static bool	find_texture_element_path(int fd_sd, char **element,
		t_parsing *parsing, t_cub3d *cub3d)
{
	char	*element_buff;

	element_buff = NULL;
	if (read(fd_sd, parsing->buff, 1) == -1)
		return (error_handler(cub3d, ELEMENT_MISS, FILE_ERR_3, MSG_6));
	while (parsing->buff[0] == ' ')
		if (read(fd_sd, parsing->buff, 1) == -1)
			return (error_handler(cub3d, ELEMENT_MISS, FILE_ERR_4, MSG_6));
	element_buff = get_next_line(fd_sd);
	if (!element_buff)
		return (error_handler(cub3d, GNL_FAILED, FILE_ERR_5, MSG_9));
	*element = ft_strjoin(parsing->buff, element_buff);
	if (!*element)
	{
		free(element_buff);
		return (error_handler(cub3d, STRJOIN_FAILED,
				"element_texture_parsing.c:66 ", MSG_10));
	}
	free(element_buff);
	*element = new_line_remover(*element);
	if (!*element)
		return (error_handler(cub3d, ELEMENT_MISS,
				"element_texture_parsing.c:74 ", MSG_6));
	return (RETURN_SUCCESS);
}

// 1) check if the char next to the first one is the right one
//    AND
//    that we are not dealing with a double entry.
//    if all clear we go to retrieve and convert the given path into our struct.

bool	is_texture_valid(int fd_sd, t_cub3d *cub3d, char fl, char sl)
{
	if (((fl == 'N' && sl == 'O') && !cub3d->parsing->rp_no))
	{
		return (find_texture_element_path(fd_sd, &cub3d->parsing->rp_no,
				cub3d->parsing, cub3d));
	}
	else if (((fl == 'S' && sl == 'O') && !cub3d->parsing->rp_so))
	{
		return (find_texture_element_path(fd_sd, &cub3d->parsing->rp_so,
				cub3d->parsing, cub3d));
	}
	else if ((fl == 'W' && sl == 'E') && !cub3d->parsing->rp_we)
	{
		return (find_texture_element_path(fd_sd, &cub3d->parsing->rp_we,
				cub3d->parsing, cub3d));
	}
	else if (fl == 'E' && sl == 'A' && !cub3d->parsing->rp_ea)
	{
		return (find_texture_element_path(fd_sd, &cub3d->parsing->rp_ea,
				cub3d->parsing, cub3d));
	}
	return (error_handler(cub3d, INV_CON_ELE, FILE_ERR_2, MSG_19));
	return (RETURN_FAILURE);
}
