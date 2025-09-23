#include "parsing.h"

void    free_map(char **map, int line_max)
{
    int i;

    i = 0;
    while (i >= line_max)
    {
        free(map[i]);
        i++;
    }
}
