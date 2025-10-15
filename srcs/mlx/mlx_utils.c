#include "exec.h"
#include "set_mlx.h"

// Here we hook and loop for the libx to handle the interaction with the window
// and loop until the ESC key is used or if the user click on the exit cross

void	hook_and_loop(t_cub3d *cub3d, t_mlx *screen)
{
	mlx_hook(screen->mlx_win, 17, 1L << 17, close_window, screen);
	mlx_hook(screen->mlx_win, 2, 1L << 0, handle_keys, screen);
	mlx_loop_hook(screen->mlx, exec, cub3d);
	mlx_loop(screen->mlx);
}

// Destroy and free everything in the right order (mostly used when the init)
// went well

void	destroy_free_screen(t_mlx *screen)
{
	mlx_destroy_image(screen->mlx, screen->screen->img);
	mlx_destroy_window(screen->mlx, screen->mlx_win);
	mlx_destroy_display(screen->mlx);
	free(screen->mlx);
	free(screen);
}

// if something went wrong during init
// destroy window (if created) then display(if created) before freeing our t_mlx
// in the right order then we return NULL to signal Main that something went
// wrong

static char	*crush_kill_destroy(void *mlx, void *win, t_mlx *t_mlx)
{
	if (win)
		mlx_destroy_window(mlx, win);
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

void	*init_screen_mlx(t_mlx *t_mlx)
{
	t_mlx = ft_calloc(1, sizeof(*t_mlx));
	if (!t_mlx)
		return (NULL);
	t_mlx->mlx = mlx_init();
	if (!t_mlx->mlx)
		return (crush_kill_destroy(NULL, NULL, t_mlx));
	t_mlx->mlx_win = mlx_new_window(t_mlx->mlx, WIN_WIDTH, WIN_HEIGHT,
			"Unforeseen consequences");
	if (!t_mlx->mlx_win)
		return (crush_kill_destroy(t_mlx->mlx, NULL, t_mlx));
	t_mlx->screen->img = mlx_new_image(t_mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!t_mlx->screen->img)
		return (crush_kill_destroy(t_mlx->mlx, t_mlx->mlx_win, t_mlx));
	t_mlx->screen->addr = mlx_get_data_addr(t_mlx->screen->img,
			&(t_mlx->screen->bits_per_pixel), &(t_mlx->screen->line_length),
			&(t_mlx->screen->endian));
	t_mlx->screen->bits_per_pixel = t_mlx->screen->bits_per_pixel >> 3;
	return (t_mlx);
}
