
#include "set_mlx.h"

int	close_window(t_set_call *param)
{
	if (param->screen->mlx_win)
		mlx_loop_end(param->screen->mlx);
	if (param->screen->img.img)
		mlx_destroy_image(param->screen->mlx, param->screen->img.img);
	if (param->screen->mlx_win)
		mlx_destroy_window(param->screen->mlx, param->screen->mlx_win);
	if (param->screen->mlx)
	{
		mlx_destroy_display(param->screen->mlx);
		free(param->screen->mlx);
	}
	free(param->c);
	free(param->z);
	free(param->screen);
	exit(0);
}

// int	key_move(int keycode, t_set_call *param)
// {
// 	//TODO?
//     return(RETURN_SUCCESS);
// }

int	handle_keys(int keycode, t_set_call *param)
{
	write(2,"test\n", 5);
    printf("key : %d\n", keycode);
	if (keycode == 65307)
		return (close_window(param));
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