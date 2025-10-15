#include "exec.h"

// put a single pixel in our image, we just require the mlx->img address
// + coordinates X(WIDTH) Y(HEIGHT) and the hexadecimal code for the color
// ALWAYS DEFINE A COLOR IF NEEDED dont put it raw you psycho.

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (y * img->line_length + x
				* (img->bits_per_pixel))) = color;
}

// function to draw our pixels
// ATM it just paint all pixel into RED color simple

int	draw_one_pixel(t_mlx *mlx, unsigned int pixel_color)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(&(mlx->img), x, y, pixel_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img->img, 0, 0);
	return (0);
}
