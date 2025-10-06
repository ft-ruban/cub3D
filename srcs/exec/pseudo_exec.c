#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// use the mlx functions to go from xpm file, to a data we can travel into.
bool	get_texture_data()
{
	img_ptr = mlx_xpm_file_to_image();
	img_data = mlx_get_data_addr();
}

// the texture is contain in a linear tab, so to find the next pixel, just add
// width to our current position.
// this function return the color_code of the pixel in a char *.
char	*get_texture_pixel()
{
	color = data->texture[i];
}





// first, find the exact position of our player, adding 0.5 to pu him in the center of
// the case mesuring 1 * 1.
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
					break;
				}
			width++;
		}
		height++;
	}
}

void	find_player_orientation(t_data *data, char c)
{
	if (c = 'N')
		data->player_orientation = M_PI/2;
	if (c = 'S')
		data->player_orientation = M_PI + M_PI/2;
	if (c = 'E')
		data->player_orientation = M_PI;
	if (c = 'W')
		data->player_orientation = 0;
}

// we are looking for the direction of the ray in the center of the player 
// vision.
// here 0 is x and 1 is y, two numbers for the main vecteur in 2D.
void	set_main_ray_dir_and_plane(t_data *data, float player_orientation)
{
	data->main_ray_dir = malloc(sizeof(float) * 4);
	data->main_ray_dir[0] = cos(data->player_orientation);
	data->main_ray_dir[1] = sin(data->player_orientation);
	data->main_ray_dir[2] = cos(data->player_orientation + M_PI/2);
	data->main_ray_dir[3] = sin(data->player_orientation + M_PI/2);
}

// after getting the main_ray_dir and his plane vecteur, we calculate the rays
// for each camera position.
void	set_all_ray_dir(t_data *data)
{
	int	i;
	int curr_column;
	float	camera;

	i = 0;
	curr_column = 0;
	data->all_ray_dir = malloc(sizeof(float) * (WIN_WIDTH * 2));
	while (i < (WIN_WIDTH * 2))
	{
		camera = 2 * (curr_column / WIN_WIDTH) - 1;
		data->all_ray_dir[i] = data->main_ray_dir[0] +
						(data->main_ray_dir[2] * camera);
		i++;
		data->all_ray_dir[i] = data->main_ray_dir[0] +
						(data->main_ray_dir[3] * camera);
		i++;
		curr_column++;
	}
}
