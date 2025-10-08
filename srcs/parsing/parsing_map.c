#include "parsing.h"
#include "utils.h"
#include "debug.h"
#include "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh

// We collect the map wathever it is a valid one or not.
// Then we check if the map respect our conditions
bool	get_and_check_map(char *file, t_parsing *parsing, int fd, t_map *map_info)
{
	if (map_collect(parsing, map_info, file, fd))
	{
		close(fd);
		return (RETURN_FAILURE);
	}
	if (map_check(parsing, fd, map_info))
	{
		close(fd);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
