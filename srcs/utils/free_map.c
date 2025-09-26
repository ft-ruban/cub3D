#include "parsing.h"

//LDEV: i -1 pour line_max?? tu peux faire i > linemax a la place :>

void    free_map_on_error(t_settings *set, int line_max)
{
    int i;

    i = 0;
    while (i >= line_max)
    {
        free(set->map[i]);
        i++;
    }
	free(set->map);
}

void	free_map(t_settings *set)
{
	int	i;

	i = 0;
	while (set->map[i])
	{
		free(set->map[i]);
		i++;
	}
	free(set->map);
}
