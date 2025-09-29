#include "parsing.h"
#include "utils.h"
#include "debug.h"
#include "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh

// We collect the map with all her possible flaws
// We check if the map respect our conditions
bool	get_and_check_map(char *file, t_settings *set, int fd)
{
	if (map_collect(set, file, fd))
	{
		close(fd);
		return (RETURN_FAILURE);
	}
	if (map_check(set, fd))
	{
		close(fd);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
