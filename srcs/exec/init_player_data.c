#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// We are looking for the direction of the ray in the center of the player 
// vision (main_ray).
// Here 0 is x and 1 is y, two numbers for a vector in 2D.

void	set_main_ray_dir_and_plane(t_ray *ray, float player_orientation)
{
	ray->main_dir_x = cos(player_orientation);
	ray->main_dir_y = sin(player_orientation);
	ray->main_plane_x = cos(player_orientation + PI * 0.5);
	ray->main_plane_y = sin(player_orientation + PI * 0.5);
}

void	assign_player_orientation(t_map *map, char player_tile)
{
	if (player_tile == 'N')
		map->player_orientation = PI * 0.5;
	if (player_tile == 'S')
		map->player_orientation = PI + PI * 0.5;
	if (player_tile == 'W')
		map->player_orientation = PI;
	if (player_tile == 'E')
		map->player_orientation = 0.0;
}

// First, find the exact position of our player, then add 0.5 to put him in the 
// center of the tile mesuring 1 * 1.

static void	find_player_pos(t_map *map_info, char **map)
{
	int		width;
	int		height;

	width = 0;
	height = 0;
	while (map[height])
	{
		width = 0;
		while (map[height][width])
		{
			if (map[height][width] == 'N' || map[height][width] == 'S' ||
				map[height][width] == 'W' || map[height][width] == 'E')
			{
				map_info->wall_pos_x = width;
				map_info->wall_pos_y = height;
				map_info->player_pos_x = width + 0.5;
				map_info->player_pos_y = height + 0.5;
				break ;
			}
			width++;
		}
		height++;
	}
}

// Locate where the player is, the direction he is facing, and the main_ray and
// plane ray associated with it. 

void	init_player_data(t_cub3d *cub3d)
{
	find_player_pos(cub3d->map, cub3d->map->map);
	assign_player_orientation(cub3d->map,
		cub3d->map->map[cub3d->map->wall_pos_y][cub3d->map->wall_pos_x]);
	set_main_ray_dir_and_plane(cub3d->ray, cub3d->map->player_orientation);
}
