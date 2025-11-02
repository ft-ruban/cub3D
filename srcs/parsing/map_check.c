/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:25:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/02 12:02:24 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// 1) we check if the case surrounding a floor is valid

static bool	surround_check(char **map, int i, int j)
{
	if (!map[j + 1])
		return (RETURN_FAILURE);
	if (map[j][i - 1] == ' ' || map[j][i - 1] == '\n' || map[j][i - 1] == '\0')
		return (RETURN_FAILURE);
	if (map[j][i + 1] == ' ' || map[j][i + 1] == '\n' || map[j][i + 1] == '\0')
		return (RETURN_FAILURE);
	if (map[j - 1][i] == ' ' || map[j - 1][i] == '\n' || map[j - 1][i] == '\0')
		return (RETURN_FAILURE);
	if (map[j + 1][i] == ' ' || map[j + 1][i] == '\n' || map[j + 1][i] == '\0')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

// 1) While reading through the map with j (map height) and i (line_width),
//    we stop on each floor or the player position to check
//    the surrounding cases.

static bool	enclosed_check(char **map)
{
	size_t	height;
	size_t	width;

	height = 0;
	while (map[height])
	{
		width = 0;
		while (map[height][width])
		{
			if (map[height][width] == '0' || map[height][width] == 'N'
				|| map[height][width] == 'S' || map[height][width] == 'E'
				|| map[height][width] == 'W')
			{
				if (surround_check(map, width, height))
					return (RETURN_FAILURE);
			}
			width++;
		}
		height++;
	}
	return (RETURN_SUCCESS);
}

// 1) We check every single characteres of the map to see if it is a valid one.
//    We check if there is no more than one player position.
static bool	map_character_check(char **map, t_cub3d *cub3d, int width,
		int height)
{
	bool	player;

	player = false;
	while (map[height])
	{
		width = 0;
		while (map[height][width] && map[height][width] != '\n')
		{
			if (map[height][width] == 'N' || map[height][width] == 'S'
				|| map[height][width] == 'E' || map[height][width] == 'W')
				if (player_update_check(&player))
					return (error_handler(cub3d, MULTIPLE_PLAYERS,
							"map_check.c:76 ", MSG_27));
			if (character_is_invalid(map[height][width]))
				return (error_handler(cub3d, INVALID_MAP_CHAR,
						"map_check.c:79 ", MSG_28));
			width++;
		}
		height++;
	}
	if (player == false)
		return (error_handler(cub3d, NO_PLAYER_FOUND, "map_check.c:86 ",
				MSG_29));
	return (RETURN_SUCCESS);
}

// 1) We just collected the map with gnl, so our first read will be on the
// 		character right after the map end.
//    From here we read until the EOF to be sure we only have '\n'.

static bool	is_map_single(t_parsing *parsing, int fd, t_cub3d *cub3d)
{
	bool	eof;
	int		read_result;

	eof = false;
	while (eof == false)
	{
		read_result = read(fd, parsing->buff, 1);
		if (read_result == READ_FAILED)
			return (error_handler(cub3d, READ_MAP_CHECK, "map_check.c:105 ",
					MSG_25));
		if (read_result == END_OF_FILE)
			eof = true;
		if (parsing->buff[0] != '\n' && eof == false)
			return (error_handler(cub3d, MAP_NOT_SINGLE, "map_check.c:110 ",
					MSG_26));
	}
	return (RETURN_SUCCESS);
}

// 1) We make sure to have only one map.
//    We check all the map characters validity.
//    We test if the floor is surrounded by walls.
bool	map_check(t_cub3d *cub3d, int fd, t_map *map_info)
{
	if (is_map_single(cub3d->parsing, fd, cub3d))
		return (RETURN_FAILURE);
	if (map_character_check(map_info->map, cub3d, 0, 0))
		return (RETURN_FAILURE);
	if (enclosed_check(map_info->map))
		return (error_handler(cub3d, MAP_NOT_ENCLOSED, "map_check.c:126 ",
				MSG_30));
	return (RETURN_SUCCESS);
}
