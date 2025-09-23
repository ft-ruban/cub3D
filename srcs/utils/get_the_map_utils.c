#include "parsing.h"

bool	is_all_map_copied(t_settings *set, size_t line_index, size_t map_height, int fd)
{
	// printf("i: %zu, height: %zu\n", line_index, map_height);
	if (line_index != map_height)
	{
		free_map(set->map, line_index);
		close(fd);
		return(error_handler(set, MAL_ERR_SET, "get_the_map.c:10", MSG_1));
	}
	return (RETURN_SUCCESS);
}

bool	find_map_start(t_settings *set, int fd)
{
	while (set->buff[0] == '\n')
		if (read(fd, set->buff, 1) == -1)
			return(error_handler(set, INV_READ, "get_the_map.c:104", MSG_6));
	return (RETURN_SUCCESS);
}

void       update_map_size(size_t *map_width, size_t *map_width_max, size_t *map_height)
{
	(*map_height)++;
	if (*map_width > *map_width_max)
		*map_width_max = *map_width;
	*map_width = 0;
}
