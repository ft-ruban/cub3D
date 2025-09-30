#include "parsing.h"
#include "utils.h"

// we check if the case surrounding a floor is valid
static bool	surround_check(char **map, int i, int j)
{
	if (map[j][i -1] == ' ' || map[j][i -1] == '\n'
		|| map[j][i -1] == '\0' || map[j][i +1] == ' '
		|| map[j][i +1] == '\n' || map[j][i +1] == '\0'
		|| map[j -1][i] == ' ' || map[j -1][i] == '\n'
		|| map[j -1][i] == '\0' || map[j +1][i] == ' '
		|| map[j +1][i] == '\n' || map[j +1][i] == '\0')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

// While reading through the map with j (map height) and i (line_width),
// we stop on each floor or the player position to check the surrounding cases.
static bool	enclosed_check(t_settings *set, char **map)
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
					return (error_handler(set, INV_MAP, "map_check.c:35 ",
							MSG_15));
			}
			width++;
		}
		height++;
	}
	return (RETURN_SUCCESS);
}

// We check every single characteres of the map to see if it is a valid one.
// We check if there is no more than one player position.
static bool	map_character_check(t_settings *set, char **map)
{
	int		width;
	int		height;
	bool	player;

	width = 0;
	height = 0;
	player = false;
	while (map[height])
	{
		width = 0;
		while (map[height][width] && map[height][width] != '\n')
		{
			if (map[height][width] == 'N' || map[height][width] == 'S'
				|| map[height][width] == 'E' || map[height][width] == 'W')
				if (player_update_check(set, &player))
					return (RETURN_FAILURE);
			if (character_is_invalid(map[height][width]))
				return (error_handler(set, INV_MAP, "map_check.c:66 ", MSG_14));
			width++;
		}
		height++;
	}
	if (player == false)
		return (error_handler(set, INV_MAP, "map_check.c:72 ", MSG_16));
	return (RETURN_SUCCESS);
}

// We just collected the map with gnl, so our first read will be on the
// character right after the map end.
// From here we read until the EOF to be sure we only have '\n'.
static bool	is_map_single(t_settings *set, int fd)
{
	bool	eof;
	int		read_result;

	eof = false;
	while (eof == false)
	{
		read_result = read(fd, set->buff, 1);
		if (read_result == READ_FAILED)
			return (error_handler(set, INV_READ, "map_check.c:89 ", MSG_6));
		if (read_result == END_OF_FILE)
			eof = true;
		if (set->buff[0] != '\n' && eof == false)
			return (error_handler(set, INV_MAP, "map_check.c:93 ", MSG_12));
	}
	return (RETURN_SUCCESS);
}

// We make sure to have only one map.
// We check all the map characters validity.
// We test if the floor is surrounded by walls.
bool	map_check(t_settings *set, int fd)
{
	if (is_map_single(set, fd))
		return (RETURN_FAILURE);
	if (map_character_check(set, set->map))
		return (RETURN_FAILURE);
	if (enclosed_check(set, set->map))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
