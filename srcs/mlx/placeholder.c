
#include "set_mlx.h"

int	draw(t_mlx *mlx)
{
	int y;
	int x;

	y = 0;
	x = 0;
	// while (y < WIN_HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < WIN_WIDTH)
	// 	{
	// 		my_mlx_pixel_put(&(mlx->img), x, y, 0x00FF0000);
	// 		x++;
	// 	}
	// 	y++;
	// }
	//my_mlx_pixel_put(&(mlx->img), x, y, 0x00FF0000);
	mlx_pixel_put(mlx->mlx, mlx->mlx_win, 10, 10, 0x00FF0000);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	*(unsigned int *)(data->addr + (y * data->line_length + x
				* (data->bits_per_pixel))) = color;
}

// to free everything before leaving

// int	free_all_mlx(t_mlx *screen, t_set_call *param, int error_code)
// {
// 	if (screen)
// 		free(screen);
// 	if (param->c)
// 		free(param->c);
// 	if (param->z)
// 		free(param->z);
// 	if (error_code == 6)
// 		return (RETURN_FAILURE);
// 	if (error_code == -1)
// 		return (1);
// 	else
// 		return (RETURN_FAILURE);
// }

void	*init_screen_mlx(t_mlx *t_mlx)
{
	t_mlx->mlx = mlx_init();
	if (!t_mlx->mlx)
		return (NULL);
	t_mlx->mlx_win = mlx_new_window(t_mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Unforeseen consequences");
	if (!t_mlx->mlx_win)
	{
		mlx_destroy_display(t_mlx->mlx);
		free(t_mlx->mlx);
		return (NULL);
	}
	t_mlx->img.img = mlx_new_image(t_mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!t_mlx->img.img)
	{
		mlx_destroy_window(t_mlx->mlx, t_mlx->mlx_win);
		mlx_destroy_display(t_mlx->mlx);
		free(t_mlx->mlx);
		return (NULL);
	}
	t_mlx->img.addr = mlx_get_data_addr(t_mlx->img.img,
			&(t_mlx->img.bits_per_pixel), &(t_mlx->img.line_length),
			&(t_mlx->img.endian));
	t_mlx->img.bits_per_pixel = t_mlx->img.bits_per_pixel >> 3;
	//my_mlx_pixel_put(&(t_mlx->img), 0, 0, 0x00FF0000);
	//mlx_put_image_to_window(t_mlx->mlx, t_mlx->mlx_win, t_mlx->img.img, 0, 0);
	return (t_mlx);
}

// init parameter that would be used during
// our cub3D 
int	init_param()
{
	printf("tuez moi\n");
	return(0);
}