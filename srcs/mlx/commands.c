#include "set_mlx.h"

// LDEV: can be completed with more key code for further commands
// 65361 = left arrow
// 65362 = up arrow
// 65363 = right arrow
// 65364 = bottom arrow
// use the printf of the keycode to find new keycode AND DEFINE for better
// readability
// USE FORMAT: KEY_LEFTARR | KEY_X

// stop the loop to make our loop stop to close the windows properly and exit
// the program


// 1) With a negative rotation, here we are gonna update every data related to
//    our orientation.
//    So we multiply the current variables by the degre of rotation we want.
// 2) Old dir_x and plane_x are just here because we need to base the calculs
//    on the current orientation, not the one already updated.

static void	turn_left(float *main_dir_x, float *main_dir_y, float *main_plane_x,
															float *main_plane_y)
{
	float	old_dir_x;
	float	old_plane_x;
	float	r;

	old_dir_x = *main_dir_x;
	old_plane_x = *main_plane_x;
	r = -ROTATION;
	*main_dir_x = *main_dir_x * cos(r) - *main_dir_y * sin(r);
	*main_dir_y = old_dir_x * sin(r) + *main_dir_y * cos(r);
	*main_plane_x = *main_plane_x * cos(r) - *main_plane_y * sin(r);
	*main_plane_y = old_plane_x * sin(r) + *main_plane_y * cos(r);
}

// 1) With a positive rotation, here we are gonna update every data related to
//    our orientation.
//    So we multiply the current variables by the degre of rotation we want.
// 2) Old dir_x and plane_x are just here because we need to base the calculs
//    on the current orientation, not the one already updated.

static void	turn_right(float *main_dir_x, float *main_dir_y,
							float *main_plane_x, float *main_plane_y)
{
	float	old_dir_x;
	float	old_plane_x;
	float	r;

	old_dir_x = *main_dir_x;
	old_plane_x = *main_plane_x;
	r = ROTATION;
	*main_dir_x = *main_dir_x * cos(r) - *main_dir_y * sin(r);
	*main_dir_y = old_dir_x * sin(r) + *main_dir_y * cos(r);
	*main_plane_x = *main_plane_x * cos(r) - *main_plane_y * sin(r);
	*main_plane_y = old_plane_x * sin(r) + *main_plane_y * cos(r);
}

int	close_window(t_mlx *screen)
{
	mlx_loop_end(screen->ptr);
	return (RETURN_SUCCESS);
}

static int key_movement_check(int keycode)
{
	if (keycode == KEY_FORWARD || keycode == KEY_BACKWARD ||
		keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_W ||
		keycode == KEY_S || keycode == KEY_A || keycode == KEY_D)
		return (1);
	return (0);
}

// handle keys entered during the exec or program
// keycode == the key used before entering into function
// LDEV: Use the printf to know which keycode we need for a specific key
// 			and define it for readability + better futur maintenance.

int	handle_keys(int keycode, t_cub3d *cub3d)
{
	printf("key : %d\n", keycode); // TODL USED TO FIND KEY CODES
	if (key_movement_check(keycode))
	{
		cub3d->print = true;
	if (keycode == KEY_FORWARD || keycode == KEY_W)
		go_forward(cub3d, cub3d->ray, cub3d->map);
	if (keycode == KEY_BACKWARD || keycode == KEY_S)
		go_backward(cub3d, cub3d->ray, cub3d->map);
	if (keycode == KEY_A)
		go_left(cub3d, cub3d->ray, cub3d->map);
	if (keycode == KEY_D)
		go_right(cub3d, cub3d->ray, cub3d->map);
	if (keycode == KEY_LEFT)
		turn_left(&cub3d->ray->main_dir_x, &cub3d->ray->main_dir_y, 
				&cub3d->ray->main_plane_x, &cub3d->ray->main_plane_y);
	if (keycode == KEY_RIGHT)
		turn_right(&cub3d->ray->main_dir_x, &cub3d->ray->main_dir_y,
				&cub3d->ray->main_plane_x, &cub3d->ray->main_plane_y);
	}
    else if (keycode == KEY_ESC)
		return (close_window(cub3d->mlx));
	return (KEY_UNKNOWN);
}
