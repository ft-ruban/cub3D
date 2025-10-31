#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

static void	print_screen(t_cub3d *cub3d)
{
	cub3d->curr_column = 0;
	while (cub3d->curr_column < WIN_WIDTH)
	{
		ray_casting(cub3d);
		column_pixels_update(cub3d);
		cub3d->curr_column++;
	}
	mlx_put_image_to_window(cub3d->mlx->ptr, cub3d->mlx->mlx_win,
									cub3d->mlx->screen->img, 0, 0);
}

int		exec(t_cub3d *cub3d)
{
	
	if (cub3d->print == true)
		print_screen(cub3d);
	cub3d->print = false;
	return (RETURN_SUCCESS);
}
