#include "exec.h"

static void	my_mlx_pixel_put(t_img *screen, int x, int y, int color)
{
	*(unsigned int *)(screen->addr + (y * screen->line_length + x
				* (screen->bits_per_pixel))) = color;
}

// function to draw our pixels
// ATM it just paint all pixel into RED color simple

int	draw(t_mlx *mlx)
{
	int	y;
	int	x;
	unsigned int	pixel_color;

	y = 0;
	x = 0;
	pixel_color = 0x0017065c;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(mlx->screen, x, y, pixel_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->screen->img, 0, 0);
	return (0);
}
