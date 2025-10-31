/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_texture_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:30:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/10/31 09:55:28 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

// read a single char, if EOF return error,
// if space we read until it is not a space in the buff anymore
// here we do a gnl to get the line that should have the right content
// if not it would be detected during the init of minilibx anyway

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
				"element_texture_parsing.c:62 ", MSG_10));
	}
	free(element_buff);
	*element = new_line_remover(*element);
	if (!*element)
		return (error_handler(cub3d, ELEMENT_MISS,
				"element_texture_parsing.c:69 ", MSG_6));
	return (RETURN_SUCCESS);
}
// if fail here it mean we already got the information
// so invalid file's content. Else we go to find the path
// to fill the ptr that point to the right variable in oru struct

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
