
#include "parsing.h"
#include "utils.h"
#include "debug.h"
#include "linux/limits.h"
#include <stdio.h> //printf TORM
#include <stdbool.h> //bool duh

bool get_and_check_map(char *file, t_settings *set, int fd)
{
    if (get_the_map(set, file, fd))
    {
        close(fd);
        return (RETURN_FAILURE);
    }
    if (check_the_map(set, fd))
    {
        close(fd);
        return (RETURN_FAILURE);
    }
    return (RETURN_SUCCESS);
}
