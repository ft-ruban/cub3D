#include "exec.h"

// function to draw our pixels
// ATM it just paint all pixel into RED color simple

int	draw(t_mlx *mlx)
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
			my_mlx_pixel_put(&(mlx->img), x, y, 0x00F0FF00);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (0);
}

// put a single pixel in our image, we just require the mlx->img address
// + coordinates X(WIDTH) Y(HEIGHT) and the hexadecimal code for the color
// ALWAYS DEFINE A COLOR IF NEEDED dont put it raw you psycho.

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	*(unsigned int *)(data->addr + (y * data->line_length + x
				* (data->bits_per_pixel))) = color;
}
