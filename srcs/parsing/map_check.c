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
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
			{
				if (surround_check(map, i, j))
					return (error_handler(set, INV_MAP, "map_check.c:34 ",
							MSG_15));
			}
			i++;
		}
		j++;
	}
	return (RETURN_SUCCESS);
}

// We check every single characteres of the map to see if it is a valid one.
// We check if there is no more than one player position.
static bool	element_check(t_settings *set, char **map)
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
				return (error_handler(set, INV_MAP, "map_check.c:65 ", MSG_14));
			width++;
		}
		height++;
	}
	if (player == false)
		return (error_handler(set, INV_MAP, "map_check.c:71 ", MSG_16));
	return (RETURN_SUCCESS);
}

// We just collected the map with gnl, so our first read will be on the
// character right after the map end.
// From here we read until the EOF to be sure we only have '\n'.
static bool	map_nbr_check(t_settings *set, int fd)
{
	bool	map_end;
	int		read_result;

	map_end = false;
	while (map_end != true)
	{
		read_result = read(fd, set->buff, 1);
		if (read_result == -1)
			return (error_handler(set, INV_READ, "map_check.c:88 ", MSG_6));
		if (read_result == 0)
			map_end = true;
		if (set->buff[0] != '\n' && set->buff[0] != '\0' && map_end != true)
			return (error_handler(set, INV_MAP, "map_check.c:92 ", MSG_12));
	}
	return (RETURN_SUCCESS);
}

// We make sure to have only one map.
// We check all the map characters validity.
// We test if the floor is surrounded by walls.
bool	map_check(t_settings *set, int fd)
{
	if (map_nbr_check(set, fd))
		return (RETURN_FAILURE);
	if (element_check(set, set->map))
		return (RETURN_FAILURE);
	if (enclosed_check(set, set->map))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
