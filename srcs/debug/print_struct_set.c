

#include "cub3D.h"
#include "debug.h"
#include "parsing.h"

//function to print the content of set (USE IT FOR DEBUG ONLY)

void	print_struct_parsing(t_parsing *parsing)
{
	printf("\n\nDEBUG\nrp_no = %s\n", parsing->rp_no);
	printf("rp_so = %s\n", parsing->rp_so);
	printf("rp_we = %s\n", parsing->rp_we);
	printf("rp_ea = %s\n", parsing->rp_ea);
	printf("floor_r = %d\n", parsing->floor_r);
	printf("floor_g = %d\n", parsing->floor_g);
	printf("floor_b = %d\n", parsing->floor_b);
	printf("cell_r = %d\n", parsing->ceil_r);
	printf("cell_g = %d\n", parsing->ceil_g);
	printf("cell_b = %d\n", parsing->ceil_b);
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
