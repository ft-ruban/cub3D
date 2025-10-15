#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// the start of the wall will be at the center of the screen with substracting
// the the height of the wall with win_height, but we went to far, so we only
// keep the half of this result.
// by doing so, we start and stop exactly at the same distance from the center.

void	pinpoint_wall_start_end(unsigned int wall_pixel_height,
				unsigned int *wall_start, unsigned int *wall_end)
{
	if (wall_pixel_height >= WIN_HEIGHT)
	{
		*wall_start = 0;
		*wall_end = WIN_HEIGHT - 1;
	}
	else
	{
		*wall_start = (WIN_HEIGHT - wall_pixel_height) / 2;
		*wall_end = *wall_start + wall_pixel_height - 1;
	}
}

// we don't use wall_dist, wich will create a fish eye. Instead we calculate
// the perpendicular distance with the main_ray.
// and we find the wall_height thanks to the win_height divided by the
// perp_wall_dist.

void	identify_wall_height(t_ray *ray, t_map *map, t_texture *texture)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (map->wall_pos_x - map->player_pos_x +
						(1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (map->wall_pos_y - map->player_pos_y +
						(1 - ray->step_y) / 2) / ray->dir_y;
	texture->wall_pixel_height = (unsigned int)(WIN_HEIGHT /
											ray->perp_wall_dist);
}

// First, find the right distance and deduct the wall height in pixel.
// we then deduct where the wall start and stop on the screen.
// a calcul must be done to know how much of the texture pixel we need, 100% of
// them ? 50% or 124.6518% ?
// and know we can take the right pixels of our texture, to print them on our
// screen img.

void	draw_column(t_cub3d *cub3d)
{
	unsigned int	wall_start;
	unsigned int	wall_end;

	wall_start = 0;
	wall_end = 0;
	identify_wall_height(cub3d->ray, cub3d->map, cub3d->texture);
	pinpoint_wall_start_end(cub3d->texture->wall_pixel_height, &wall_start,
																&wall_end);
	draw_all_pixels(cub3d, cub3d->texture, wall_start, wall_end);
}
