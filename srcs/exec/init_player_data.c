#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// first, find the exact position of our player, adding 0.5 to pu him in the 
// center of the case mesuring 1 * 1.
void	find_player_pos(t_data *data, char **map)
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
					data->map_x = width;
					data->map_y = height;
					data->pos_x = width + 0.5;
					data->pos_y = height + 0.5;
					assign_player_orientation(data, map[height][width]);
					break;
				}
			width++;
		}
		height++;
	}
}

void	assign_player_orientation(t_data *data, char c)
{
	if (c = 'N')
		data->player_orientation = M_PI * 0.5;
	if (c = 'S')
		data->player_orientation = M_PI + M_PI * 0.5;
	if (c = 'W')
		data->player_orientation = M_PI;
	if (c = 'E')
		data->player_orientation = 0.0;
}

// we are looking for the direction of the ray in the center of the player 
// vision.
// here 0 is x and 1 is y, two numbers for the main vecteur in 2D.
void	set_main_ray_dir_and_plane(t_data *data, float player_orientation)
{
	data->main_ray_dir_x = cos(data->player_orientation);
	data->main_ray_dir_y = sin(data->player_orientation);
	data->main_ray_plane_x = cos(data->player_orientation + M_PI * 0.5);
	data->main_ray_plane_y = sin(data->player_orientation + M_PI * 0.5);
}
