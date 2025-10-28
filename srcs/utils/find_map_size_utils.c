#include "parsing.h"

// Comparing the line_index to the map_height to be sure we got all the map
bool	is_all_map_copied(t_cub3d *cub3d, size_t line_index, size_t map_height,
	int fd)
{
	if (line_index != map_height)
	{
		free_map(cub3d->map);
		close(fd);
		return (error_handler(cub3d, MAL_ERR_BUFF, "get_the_map.c:10", MSG_1));
	}
	return (RETURN_SUCCESS);
}

bool	find_map_start(t_parsing *parsing, int fd, t_cub3d *cub3d)
{
	while (parsing->buff[0] == '\n')
		if (read(fd, parsing->buff, 1) == -1)
			return (error_handler(cub3d, FAIL_READ_MAP, "get_the_map.c:104", MSG_22)); //13
	return (RETURN_SUCCESS);
}
