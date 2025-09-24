#include "parsing.h"

int    find_map_start(t_settings *set, int fd)
{
    while (set->buff[0] == '\n')
		if (read(fd, set->buff, 1) == -1)
			return(error_handler(set, INV_READ, "get_the_map.c:104", MSG_6));
    return (RETURN_SUCCESS);
}

void       update_width_height(int *map_width, int *map_width_max, int *map_height)
{
    (*map_height)++;
    if (*map_width > *map_width_max)
        *map_width_max = *map_width;
    *map_width = 0;
}
