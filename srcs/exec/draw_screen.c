#include "exec.h"

// function to draw our pixels

int	draw_screen(t_mlx *mlx)
{
	// int	printed_column;

	// printed_column = 0;
	// while (printed_column < WIN_WIDTH)
	// {
	// 	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->screen->img,
	// 													printed_column, 0);
	// 	printed_column++;
	// }
	mlx_put_image_to_window(mlx->ptr, mlx->mlx_win, mlx->screen->img, 0, 0);
	return (0);
}
