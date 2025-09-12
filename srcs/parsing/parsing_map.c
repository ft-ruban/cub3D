
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
    if (element_check(set->map))
        return (RETURN_FAILURE);
    if (enclosed_check(set->map))
        return (RETURN_FAILURE);
    return (RETURN_FAILURE);
}

int get_the_map(t_settings *set, char *file, int fd)
{
    int map_width;
    int map_height;

    map_width = 0;
    map_height = 0;
    if (find_map_size(set, &map_width, &map_height, fd))
        return (RETURN_FAILURE);
    // printf("height: %d, width: %d\n", map_height, map_width);
    if (malloc_map(set, map_width, map_height, &(set->map)))
        return (RETURN_FAILURE);
    fd = read_until_map_start(file, set, fd);
    if (fd == RETURN_FAILURE)
        return (RETURN_FAILURE);
    if (cpy_the_map(set, set->map, map_height, fd))
         return (RETURN_FAILURE);
    return (RETURN_SUCCESS);
}

int get_and_check_map(char *file, t_settings *set, int fd)
{
    if (get_the_map(set, file, fd))
    {
        close(fd);
        return (RETURN_FAILURE);
    }
    // print_map(set);
    if (check_the_map(set, fd))
    {
        close(fd);
        return (RETURN_FAILURE);
    }
    return (RETURN_SUCCESS);
}
