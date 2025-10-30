#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// create/stock the xpm file to a mlx file we can use with the mlx functions.
// stock the address of mlx image we got in a char *, update bits_per_pixel to
// know how many bits to have a complete pixel (here it is 32). We can now pick the pixel
// we need in that linear tab of char going from .
bool	get_texture_data(t_cub3d *cub3d, t_img *img, char *path)
{
	int	width;
	int	height;

	width = TEXTURE_WIDTH;
	height = TEXTURE_HEIGHT;
	img->img = mlx_xpm_file_to_image(cub3d->mlx->ptr, path,
								&width, &height); // TODO LDEV : protect
	if (!img->img)
		return (error_handler(cub3d, MAL_ERR_BUFF, "exec:TOFILL ", MSG_1));
	img->addr = mlx_get_data_addr(img->img,
			&(img->bits_per_pixel), &(img->line_length),
			&(img->endian));
	if (!img->addr)
		return (error_handler(cub3d, MAL_ERR_BUFF, "exec:TOFILL ", MSG_1));
	return (RETURN_SUCCESS);
}

int		exec(t_cub3d *cub3d)
{
	init_player_data(cub3d);
	print_screen(cub3d);
	return (RETURN_SUCCESS);
}
