#include "parsing.h"

static bool enclosed_check(t_settings *set, char **map)
{
    int i;
    int j;

    j = 0;
    while (map[j])
    {
        i = 0;
        while(map[j][i])
        {
            if (map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W')
            {
                if (map[j][i -1] == ' ' || map[j][i -1] == '\n' || map[j][i -1] == '\0'
					|| map[j][i +1] == ' ' || map[j][i +1] == '\n' || map[j][i +1] == '\0'
					|| map[j -1][i] == ' ' || map[j -1][i] == '\n' || map[j -1][i] == '\0'
					|| map[j +1][i] == ' ' || map[j +1][i] == '\n' || map[j +1][i] == '\0')
                	return (error_handler(set, INV_MAP, "check_the_map.c.c:19 ", MSG_15));
            }
            i++;
        }
        j++;
    }
    return (RETURN_SUCCESS);
}

static bool	character_is_invalid(char c)
{
	if (c != '1' && c != '0' && c != 'N'
    	&& c != 'S' && c != 'E' && c != 'W'
    	&& c != '\0' && c != '\n' && c != ' ')
    	return (RETURN_FAILURE);
	else
		return (RETURN_SUCCESS);
}

bool	player_update_check(t_settings *set, bool *player)
{
	if (*player == true)
		return (error_handler(set, INV_MAP, "check_the_map.c.c:55 ", MSG_13));
	else
		*player = true;
	return (RETURN_SUCCESS);
}

static bool element_check(t_settings *set, char **map)
{
    int width;
    int height;
    bool player;

	width = 0;
    height = 0;
	player = false;
    while (map[height])
    {
		width = 0;
        while(map[height][width] && map[height][width] != '\n')
        {
            if (map[height][width] == 'N' || map[height][width] == 'S'
				|| map[height][width] == 'E' || map[height][width] == 'W')
				if (player_update_check(set, &player))
					return (RETURN_FAILURE);
            if (character_is_invalid(map[height][width]))
                return (error_handler(set, INV_MAP, "check_the_map.c.c:60 ", MSG_14));
            width++;
        }
        height++;
    }
    return (RETURN_SUCCESS);
}

static bool map_nbr_check(t_settings *set, int fd)
{
	bool map_end;
	int	read_result;

	map_end = false;
	if (read(fd, set->buff, 1) == -1)
		return(error_handler(set, INV_READ, "get_the_map.c:116", MSG_6));
    while(map_end != true)
    {
		read_result = read(fd, set->buff, 1);
		if (read_result == -1)
			return(error_handler(set, INV_READ, "get_the_map.c:116", MSG_6));
		if (read_result == 0)
			map_end = true;
        if (set->buff[0] != '\n' && set->buff[0] != '\0' && map_end != true)
            return(error_handler(set, INV_MAP, "check_the_map.c.c:72 ", MSG_12));
    }
    return (RETURN_SUCCESS);
}

bool check_the_map(t_settings *set, int fd)
{
    if (map_nbr_check(set, fd))
        return (RETURN_FAILURE);
    if (element_check(set, set->map))
		return (RETURN_FAILURE);
	if (enclosed_check(set, set->map))
        return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}
