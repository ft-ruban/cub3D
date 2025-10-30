#include "exec.h"
#include "set_mlx.h"

// Here we hook and loop for the libx to handle the interaction with the window
// and loop until the ESC key is used or if the user click on the exit cross

// void	hook_and_loop(t_cub3d *cub3d, t_mlx *mlx)
// {
// 	(void)cub3d;
// 	mlx_hook(mlx->mlx_win, 17, 1L << 17, close_window, mlx);
// 	mlx_hook(mlx->mlx_win, 2, 1L << 0, handle_keys, mlx);
// 	mlx_loop_hook(mlx->mlx, draw, mlx);
// 	mlx_loop(mlx->mlx);
// }

// Destroy and free everything in the right order (mostly used when the init)
// went well

// void	destroy_free_screen(t_mlx *mlx)
// {
// 	mlx_destroy_image(mlx->mlx, mlx->screen->img);
// 	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
// 	mlx_destroy_display(mlx->mlx);
// 	free(mlx->mlx);
// 	free(mlx);
// }

// bool	init_screen(t_mlx *mlx)
// {
// 	t_img	*screen;

// 	screen = malloc(sizeof(t_img));
// 	if (!screen)
// 		return (RETURN_FAILURE);
// 	mlx->screen = screen;
// 	return (RETURN_SUCCESS);
// }

// if something went wrong during init
// destroy window (if created) then display(if created) before freeing our t_mlx
// in the right order then we return NULL to signal Main that something went
// wrong

static char	*crush_kill_destroy(void *mlx, void *win, t_mlx *t_mlx, t_img *screen)
{
	if (win)
		mlx_destroy_window(mlx, win);
	if (screen)
		free(screen);
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
	free(t_mlx);
	return (NULL);
}

// here we malloc our t_mlx structure, then we init mlx then we use a
// function(mlx_new_window) creates a new window on the screen
// using the size_x and size_y parameters to determine its size
// + name of window,
// then with (mlx_new_image) we creates a new image in memory
// then(mlx_get_data_addr)returns information about the created image,
// allowing the user to modify it later if necessary.
// if any of those fail then we exit properly thanks to crush_kill_destroy

void	*init_screen_mlx(t_cub3d *cub3d, t_mlx *mlx)
{
	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return(error_handler_void(cub3d, INIT_MLX_FAIL, "TOFILL", MSG_31));
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (crush_kill_destroy(NULL, NULL, mlx, NULL));
	// mlx->mlx_win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT,
	// 		"Unforeseen consequences");
	// if (!mlx->mlx_win)
	// 	return (crush_kill_destroy(mlx->mlx, NULL, mlx, NULL));
	// if (init_screen(mlx))
	// 	return (crush_kill_destroy(mlx->mlx, mlx->mlx_win, mlx, NULL));
	// mlx->screen->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	// if (!mlx->screen->img)
	// 	return (crush_kill_destroy(mlx->mlx, mlx->mlx_win, mlx, mlx->screen));
	// mlx->screen->addr = mlx_get_data_addr(mlx->screen->img,
	// 		&(mlx->screen->bits_per_pixel), &(mlx->screen->line_length),
	// 		&(mlx->screen->endian));
	// mlx->screen->bits_per_pixel = mlx->screen->bits_per_pixel >> 3;
	return (mlx);
}
