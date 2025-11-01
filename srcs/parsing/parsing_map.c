/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:26:38 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 11:55:00 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
//#include "debug.h"
//#include "linux/limits.h"
//#include "parsing.h"
//#include <stdbool.h> //bool duh
//#include <stdio.h>   //printf TORM

// We collect the map wathever it is a valid one or not.
// Then we check if the map respect our conditions
bool	get_and_check_map(char *file, t_cub3d *cub3d, int fd)
{
	t_map	*map_info;

	map_info = malloc(sizeof(t_map));
	if (!map_info)
		return (error_handler(cub3d, FAIL_INIT_MAP, "parsing_map.c:26 ",
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
