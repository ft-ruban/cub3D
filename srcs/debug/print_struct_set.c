

#include "cub3D.h"
#include "debug.h"
#include "parsing.h"

//function to print the content of set (USE IT FOR DEBUG ONLY)

void	print_struct_set(t_settings *set)
{
	printf("\n\nDEBUG\nrp_no = %s\n", set->rp_no);
	printf("rp_so = %s\n", set->rp_so);
	printf("rp_we = %s\n", set->rp_we);
	printf("rp_ea = %s\n", set->rp_ea);
	printf("floor_r = %d\n", set->floor_r);
	printf("floor_g = %d\n", set->floor_g);
	printf("floor_b = %d\n", set->floor_b);
	printf("cell_r = %d\n", set->ceil_r);
	printf("cell_g = %d\n", set->ceil_g);
	printf("cell_b = %d\n", set->ceil_b);
}

void	print_map(t_map *map_info)
{
	size_t	i;

	i = 0;
	printf("\nMAP:\n\n");
	while (map_info->map[i])
	{
		printf("map[%zu]: %s", i, map_info->map[i]);
		i++;
	}
}
