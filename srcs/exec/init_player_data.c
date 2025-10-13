#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// we are looking for the direction of the ray in the center of the player 
// vision.
// here 0 is x and 1 is y, two numbers for the main vecteur in 2D.
void	set_main_ray_dir_and_plane(t_ray *ray, float player_orientation)
{
	ray->main_ray_dir_x = cos(player_orientation);
	ray->main_ray_dir_y = sin(player_orientation);
	ray->main_ray_plane_x = cos(player_orientation + M_PI * 0.5);
	ray->main_ray_plane_y = sin(player_orientation + M_PI * 0.5);
}

void	assign_player_orientation(t_map *map, char player_tile)
{
	if (player_tile = 'N')
		map->player_orientation = M_PI * 0.5;
	if (player_tile = 'S')
		map->player_orientation = M_PI + M_PI * 0.5;
	if (player_tile = 'W')
		map->player_orientation = M_PI;
	if (player_tile = 'E')
		map->player_orientation = 0.0;
}

// first, find the exact position of our player, adding 0.5 to pu him in the 
// center of the case mesuring 1 * 1.
char	find_player_pos(t_map *map_info, char **map)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	while (map[height])
	{
		while (map[height][width])
		{
			if (map[height][width] == 'N' || map[height][width] == 'S' ||
				map[height][width] == 'W' || map[height][width] == 'E')
				{
					map_info->wall_pos_x = width;
					map_info->wall_pos_y = height;
					map_info->player_pos_x = width + 0.5;
					map_info->player_pos_y = height + 0.5;
					break;
				}
			width++;
		}
		height++;
	}
	return(map[height][width]);
}

void	init_player_data(t_cub3d *cub3d)
{
	char	player_tile;

	player_tile = find_player_pos(cub3d->map, cub3d->map->map);
	assign_player_orientation(cub3d->map, player_tile);
	set_main_ray_dir_and_plane(cub3d->ray, cub3d->map->player_orientation);
}
