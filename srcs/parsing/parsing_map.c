/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:26:38 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/02 10:26:45 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// 1) we malloc our map structure and associate the pointer of our main struct
//    to that address for convenience.
// 2) go to function that collect the map
// 3) go to function that check the map

bool	get_and_check_map(char *file, t_cub3d *cub3d, int fd)
{
	t_map	*map_info;

	map_info = malloc(sizeof(t_map));
	if (!map_info)
		return (error_handler(cub3d, FAIL_INIT_MAP, "parsing_map.c:25 ",
				MSG_20));
	cub3d->map = map_info;
	if (map_collect(cub3d, map_info, file, fd))
	{
		close(fd);
		return (RETURN_FAILURE);
	}
	if (map_check(cub3d, fd, map_info))
	{
		close(fd);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
