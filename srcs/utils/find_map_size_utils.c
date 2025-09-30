#include "parsing.h"

// Comparing the line_index to the map_height to be sure we got all the map
bool	is_all_map_copied(t_settings *set, size_t line_index, size_t map_height,
	int fd)
{
	if (line_index != map_height)
	{
		free_map(set);
		close(fd);
		return (error_handler(set, MAL_ERR_SET, "get_the_map.c:10", MSG_1));
	}
	return (RETURN_SUCCESS);
}

bool	find_map_start(t_settings *set, int fd)
{
	while (set->buff[0] == '\n')
		if (read(fd, set->buff, 1) == -1)
			return (error_handler(set, INV_READ, "get_the_map.c:104", MSG_6));
	return (RETURN_SUCCESS);
}
