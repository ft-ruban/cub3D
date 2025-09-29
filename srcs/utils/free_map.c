#include "parsing.h"

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
