
#include "parsing.h"
#include "utils.h"
#include "debug.h"
#include "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh

int check_the_map(t_settings *set, int fd)
{
    if (map_nbr_check(set, fd))
        return (RETURN_FAILURE);
    if (element_check(set, set->map))
		return (RETURN_FAILURE);
    if (enclosed_check(set, set->map, '\0'))
		return (RETURN_FAILURE);
	if (enclosed_check(set, set->map, '\n'))
		return (RETURN_FAILURE);
	if (enclosed_check(set, set->map, ' '))
        return (RETURN_FAILURE);
    printf("hey\n");
    return (RETURN_SUCCESS);
}

int get_and_check_map(char *file, t_settings *set, int fd)
{
    if (get_the_map(set, file, fd))
    {
        close(fd);
        return (RETURN_FAILURE);
    }
    print_map(set);
    if (check_the_map(set, fd))
    {
        close(fd);
        return (RETURN_FAILURE);
    }
    return (RETURN_SUCCESS);
}
