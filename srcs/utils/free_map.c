#include "parsing.h"

//LDEV: i -1 pour line_max?? tu peux faire i > linemax a la place :>

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
