/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map_size_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:59:17 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/03 21:10:49 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// Comparing the line_index to the map_height to be sure we got all the map
bool	is_all_map_copied(t_cub3d *cub3d, size_t line_index, size_t map_height,
		int fd)
{
	if (line_index != map_height)
	{
		free_map(cub3d->map);
		close(fd);
		return (error_handler(cub3d, MAL_ERR_BUFF,
				"(find_map_size_utils.c:19) ", MSG_1));
	}
	return (RETURN_SUCCESS);
}

bool	find_map_start(t_parsing *parsing, int fd)
{
	int	read_value;

	while (parsing->buff[0] == '\n')
	{
		read_value = read(fd, parsing->buff, 1);
		if (read_value == 0 || read_value == -1)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
