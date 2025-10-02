
#include "set_mlx.h"

int	close_window(t_mlx *screen)
{
	// if (screen->mlx_win)
	// 	mlx_loop_end(screen->mlx);
	// if (screen->img.img)
	// 	mlx_destroy_image(screen->mlx, screen->img.img);
	// if (screen->mlx_win)
	// 	mlx_destroy_window(screen->mlx, screen->mlx_win);
	// if (screen->mlx)
	// {
	// 	mlx_destroy_display(screen->mlx);
	// 	free(screen->mlx);
	// }
	// return(0);

	mlx_loop_end(screen->mlx);
	// mlx_destroy_image(screen->mlx, screen->img.img);
	// mlx_destroy_window(screen->mlx, screen->mlx_win);
	//mlx_destroy_display(screen->mlx);
	//free(screen->mlx);
	return(0);
}

// int	key_move(int keycode, t_set_call *param)
// {
// 	//TODO?
//     return(RETURN_SUCCESS);
// }

int	handle_keys(int keycode, t_mlx *screen)
{
	write(2,"test\n", 5);
    printf("key : %d\n", keycode);
	if (keycode == 65307)
		return (close_window(screen));
	// if (keycode == 65361 || keycode == 65362 || keycode == 65363
	// 	|| keycode == 65364)
	// 	return (key_move(keycode & 0x7, param));
	// else
	// {
	// 	if (change_color(&param->color_factor) == 1)
	// 		return (close_window(param));
	// }
	return (1);
}