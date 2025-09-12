#include "parsing.h"

int enclosed_check(char **map)
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
                if (map[j][i -1] == '\0' || map[j][i +1] == '\0'
					|| map[j -1][i] == '\0' || map[j +1][i] == '\0')
                	return (RETURN_FAILURE);
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
    	&& c != '\0')
    	return (RETURN_FAILURE);
	else
		return (RETURN_SUCCESS);
}

int element_check(char **map)
{
    int width;
    int height;
    bool player;

    height = 0;
    while (map[height])
    {
        width = 0;
        while(map[height][width])
        {
            if (map[height][width] == 'N' && map[height][width] == 'S'
                && map[height][width] == 'E' && map[height][width] == 'W')
            {
                if (player == true)
                    return (RETURN_FAILURE);
                else
                    player = true;
            }
            if (character_is_invalid(map[height][width]))
                return (RETURN_FAILURE);
            width++;
        }
        height++;
    }
    return (RETURN_SUCCESS);
}

int map_nbr_check(t_settings *set, int fd)
{
    while(read(fd, set->buff, 1) != 0) // On va jusqu'au bout du fichier
    {
		// printf("%c\n", set->buff[0]);
        if (set->buff[0] != '\n')
            return(error_handler(set, INV_MAP, "check_the_map.c.c:72 ", MSG_9));
    }
    return (RETURN_SUCCESS);
}
