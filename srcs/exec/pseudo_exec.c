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




int		exec(t_data *data, char **map)
{
	init_player_data(data, map);
	update_screen(data);
}
