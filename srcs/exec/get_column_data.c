#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// 1) The start of the wall will be at the center of the screen (WIN_HEIGHT / 2)
//    minus the half of the wall_pixel_height.
// 2) Once we have wall_start, we compute wall_end by adding the wall height to
//    it. The '-1' ensures we stay within the correct range since pixel indices
//    start at 0. (If the wall is n pixels tall, its last pixel is at index
//    n-1.)
//
// By doing so, we start and stop exactly at the same distance from the center.

static void	pinpoint_wall_start_end(t_texture *texture,
				unsigned int *wall_start, unsigned int *wall_end)
{
	texture->offset = 0;
	if (texture->wall_pixel_height >= WIN_HEIGHT)
	{
		texture->offset = -((int)((WIN_HEIGHT -
			(int)texture->wall_pixel_height) * 0.5));
		*wall_start = 0;
		*wall_end = WIN_HEIGHT - 1;
	}
	else
	{
		*wall_start = (WIN_HEIGHT - texture->wall_pixel_height) * 0.5;
		*wall_end = *wall_start + texture->wall_pixel_height - 1;
	}
}

// 1) We don't use wall_dist, wich will create a fish eye. Instead we calculate
//    the perpendicular distance from the player to the wall hit (either 
//    vertical (x) or horizontal (y)). We then divide it by the ray_dir.
//    wall_pos - player_pos is to determine the perpendicular distance from the
//    player's position to the wall.
//    If we go on the left or up, we are gonna encounter the wall sooner from 1.
//    That's why we add 1-step/2. If our step is positive it is equal to
//    0 (nothing changes), but if it is negative, it will be 1 (wich means we
//    update our wall position to wall_pos + 1).
//    Lastly, we divide this distance by the ray_dir, to have the right distance
//    depending on the ray.
// 2) To determine how tall the wall_pixel_height is we divide the WIN_HEIGHT
//    by the perp_wall_dist. So if the distance with our wall is 2, the wall
//    will appear twice smaller than the WIN_HEIGHT.
// 3) Save render, wich represent how much of the texture pixel we need, 100% of
//    them (render = 1)? 50% (render = 0.5.) or 124.6518% (render = 1.246518)?

static void	identify_wall_height(t_ray *ray, t_map *map, t_texture *texture)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (map->wall_pos_x - map->player_pos_x +
						(1 - ray->step_x) * 0.5) / ray->dir_x;
	else
		ray->perp_wall_dist = (map->wall_pos_y - map->player_pos_y +
						(1 - ray->step_y) * 0.5) / ray->dir_y;
	texture->wall_pixel_height = (unsigned int)(WIN_HEIGHT /
											ray->perp_wall_dist);
	texture->render = (double)TEXTURE_HEIGHT / texture->wall_pixel_height;
}

// 1) Get the right distance and deduct the wall height(in pixel).
// 2) Deduct where the wall start and stop on the screen.
//
// And now we can locate the right pixels of our texture, to print them on our
// screen img.

void	get_column_data(t_cub3d *cub3d)
{
	unsigned int	wall_start;
	unsigned int	wall_end;

	wall_start = 0;
	wall_end = 0;
	identify_wall_height(cub3d->ray, cub3d->map, cub3d->texture);
	pinpoint_wall_start_end(cub3d->texture, &wall_start, &wall_end);
	save_column_pixels(cub3d, cub3d->texture, wall_start, wall_end);
}
