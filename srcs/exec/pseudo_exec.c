#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// use the mlx functions to go from xpm file, to a data we can travel into.
bool	get_texture_data(t_settings *set, t_mlx *mlx, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(mlx->mlx, set->rp_no, TEXTURE_WIDTH,
			TEXTURE_HEIGHT); // TODO LDEV : protect
	texture->addr = mlx_get_data_addr(texture->img,
			&(texture->bits_per_pixel), &(texture->line_length),
			&(texture->endian)); // TODO : protect. Check if necessary 
								 // (mlx or texture ?)
}

// the texture is contain in a linear tab, so to find the next pixel, just add
// width to our current position.
// here we know the 'x' column of the pixel on the 'y' line.
// this function return the color_code of the pixel in a int.
int	get_texture_pixel(t_data *data, int x, int y)
{
	int	pixel;

	pixel = data->texture->addr[x + (y * WIN_WIDTH)];
	return (pixel);
}





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
					data->player_pos_y = height + 0.5;
					data->player_pos_x = width + 0.5;
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
		data->player_orientation = M_PI*0.5;
	if (c = 'S')
		data->player_orientation = M_PI + M_PI*0.5;
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
	data->main_ray_plane_x = cos(data->player_orientation + M_PI*0.5);
	data->main_ray_plane_y = sin(data->player_orientation + M_PI*0.5);
}

// after getting the main_ray_dir and his plane vecteur, we calculate the rays
// (for each camera position).
// for every ray, we calculate the distance in between the player and the wall,
// and then we move to the next ray.
// for every time we calculate a ray direction, the camera orient a tiny bit to
// the left, updating itself with the current ray_dir we are calculating.
void	set_all_ray_dir(t_data *data)
{
	int 	curr_column;
	float	camera;
	float	ray_dir_x;
	float	ray_dir_y;

	curr_column = 0;
	while (curr_column < WIN_WIDTH)
	{
		camera = 2 * (curr_column / WIN_WIDTH) - 1;
		ray_dir_x = data->main_ray_dir_x +
						(data->main_ray_plane_x * camera);
		ray_dir_y = data->main_ray_dir_y +
						(data->main_ray_plane_y * camera);
		tout_calculer(data, ray_dir_x, ray_dir_y);
		curr_column++;
	}
}
