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

static void	go_backward(t_cub3d *cub3d, t_ray *ray, t_map *map)
{
	if (map->map
		[(int)map->player_pos_y]
		[(int)(map->player_pos_x - (STEP * ray->main_dir_x))] != '1')
	{
		map->player_pos_x -= (STEP * ray->main_dir_x);
	}
	if (map->map
		[(int)(map->player_pos_y - (STEP * ray->main_dir_y))]
		[(int)map->player_pos_x] != '1')
	{
		map->player_pos_y -= (STEP * ray->main_dir_y);
	}
	cub3d->print = true;
}

static void	go_forward(t_cub3d *cub3d, t_ray *ray, t_map *map)
{
	if (map->map
		[(int)map->player_pos_y]
		[(int)(map->player_pos_x + (STEP * ray->main_dir_x))] != '1')
	{
		map->player_pos_x += (STEP * ray->main_dir_x);
	}
	if (map->map
		[(int)(map->player_pos_y + (STEP * ray->main_dir_y))]
		[(int)map->player_pos_x] != '1')
	{
		map->player_pos_y += (STEP * ray->main_dir_y);
	}
	cub3d->print = true;
}

int	close_window(t_mlx *screen)
{
	mlx_loop_end(screen->ptr);
	return (RETURN_SUCCESS);
}

// handle keys entered during the exec or program
// keycode == the key used before entering into function
// LDEV: Use the printf to know which keycode we need for a specific key
// 			and define it for readability + better futur maintenance.

int	handle_keys(int keycode, t_cub3d *cub3d)
{
	printf("key : %d\n", keycode); // TODL USED TO FIND KEY CODES
	if (keycode == KEY_FORWARD || keycode == KEY_BACKWARD ||
					keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		cub3d->print = true;
	if (keycode == KEY_FORWARD)
		go_forward(cub3d, cub3d->ray, cub3d->map);
	if (keycode == KEY_BACKWARD)
		go_backward(cub3d, cub3d->ray, cub3d->map);
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

// ex of use for ex
// if (keycode == 65361 || keycode == 65362 || keycode == 65363
// 	|| keycode == 65364)
// 	return (key_move(keycode & 0x7, param));
// else
// {
// 	if (change_color(&param->color_factor) == 1)
// 		return (close_window(param));
// }