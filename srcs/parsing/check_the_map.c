#include "parsing.h"

int enclosed_check(t_settings *set, char **map, char c)
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
                if (map[j][i -1] == c || map[j][i +1] == c
					|| map[j -1][i] == c || map[j +1][i] == c)
                	return (error_handler(set, INV_MAP, "check_the_map.c.c:19 ", MSG_12));
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

int element_check(t_settings *set, char **map)
{
    int width;
    int height;
    bool player;

    height = 0;
    while (map[height])
    {
        width = 0;
        while(map[height][width] && map[height][width] != '\n')
        {
            if (map[height][width] == 'N' || map[height][width] == 'S'
                || map[height][width] == 'E' || map[height][width] == 'W')
            {
                if (player == true)
                    return (error_handler(set, INV_MAP, "check_the_map.c.c:55 ", MSG_10));
                else
                    player = true;
            }
            if (character_is_invalid(map[height][width]))
                return (error_handler(set, INV_MAP, "check_the_map.c.c:60 ", MSG_11));
            width++;
        }
        height++;
    }
    return (RETURN_SUCCESS);
}

int map_nbr_check(t_settings *set, int fd)
{
    read(fd, set->buff, 1);
    while(read(fd, set->buff, 1) != 0) // On va jusqu'au bout du fichier
    {
        if (set->buff[0] != '\n' && set->buff[0] != '\0')
            return(error_handler(set, INV_MAP, "check_the_map.c.c:72 ", MSG_9));
    }
    return (RETURN_SUCCESS);
}
