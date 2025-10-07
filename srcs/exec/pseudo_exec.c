#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// create/stock the xpm file to a mlx file we can use with the mlx functions.
// stock the address of mlx image we got in a char *, update bits_per_pixel to
// know how many bits to have a complete pixel (here it is 32). We can now pick the pixel
// we need in that linear tab of char going from .
bool	get_texture_data(t_settings *set, t_mlx *mlx, t_texture *texture)
{
	texture->no_img = mlx_xpm_file_to_image(mlx->mlx, set->rp_no, TEXTURE_WIDTH,
			TEXTURE_HEIGHT); // TODO LDEV : protect
	texture->no_addr = mlx_get_data_addr(texture->no_img,
			&(texture->bits_per_pixel), &(texture->line_length),
			&(texture->endian)); // TODO : protect. Check if necessary 
								 // (mlx or texture ?)
	texture->so_img = mlx_xpm_file_to_image(mlx->mlx, set->rp_so, TEXTURE_WIDTH,
			TEXTURE_HEIGHT); // TODO LDEV : protect
	texture->so_addr = mlx_get_data_addr(texture->so_img,
			&(texture->bits_per_pixel), &(texture->line_length),
			&(texture->endian)); // TODO : protect. Check if necessary 
								 // (mlx or texture ?)
	texture->we_img = mlx_xpm_file_to_image(mlx->mlx, set->rp_we, TEXTURE_WIDTH,
			TEXTURE_HEIGHT); // TODO LDEV : protect
	texture->we_addr = mlx_get_data_addr(texture->we_img,
			&(texture->bits_per_pixel), &(texture->line_length),
			&(texture->endian)); // TODO : protect. Check if necessary 
								 // (mlx or texture ?)
	texture->ea_img = mlx_xpm_file_to_image(mlx->mlx, set->rp_ea, TEXTURE_WIDTH,
			TEXTURE_HEIGHT); // TODO LDEV : protect
	texture->ea_addr = mlx_get_data_addr(texture->ea_img,
			&(texture->bits_per_pixel), &(texture->line_length),
			&(texture->endian)); // TODO : protect. Check if necessary 
								 // (mlx or texture ?)
}

// the texture is contain in a linear tab of char, so to find the pixel we want,
// we are gonna find the right position in this tab, then we retrieve the pixel
// by taking all the four char wich represent rgba at once in a int.
// char = 8 bits, int = 32 bits. so casting an int to retrieve from a char tab,
// its gonna take four char at once (32 bits).
// the x is the column of the pixel we want, y is the line.
// to go from a line to the next one, we add line_length and not TEXTURE_WIDTH
// since the TEXTURE_WIDTH is equal to the number of pixel before next line,
// and line_length is equal to the number of char berfore next line.
unsigned int	get_texture_pixel(t_data *data, int x, int y, void *texture_adr)
{
	char			*pixel_addr;
	unsigned int	pixel_color;

	pixel_addr = texture_adr + (y * data->texture->line_length + x *
							data->texture->bits_per_pixel / 8);
	pixel_color = *(unsigned int *)pixel_addr;
	return (pixel_color);
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
