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




int		exec(t_data *data, t_settings *set, t_mlx *mlx, char **map)
{
	init_player_data(data, map);
	print_screen(data, set, mlx);
}
