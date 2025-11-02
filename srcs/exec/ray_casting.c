/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:58:40 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/02 13:15:07 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// 1) We are now on the edge of x and y, so to go forward we are gonna add
//   one dist_next_x or y. 
// 2) Before we have to choose; either go on the next x or y edge. To do so,
//   we check if the next x will arrive sooner than the next y, if that's true,
//   we add dist_next_x to wall_dist_x.
//
// Everytime we move to the next edge, we keep track of where we are by updating
// the map_x or y with the right step(+1 or -1).
// the side variable is here to indicate if we hit a wall on the x(0) or y(1)
// side.

void	until_we_hit_a_wall(t_map *map, t_ray *ray,
			double dist_next_x, double dist_next_y)
{
	while (map->map[map->wall_pos_y][map->wall_pos_x] != '1')
	{
		if (ray->wall_dist_x < ray->wall_dist_y)
		{
			ray->wall_dist_x += dist_next_x;
			map->wall_pos_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->wall_dist_y += dist_next_y;
			map->wall_pos_y += ray->step_y;
			ray->side = 1;
		}
	}
}

// 1) Depending on where we are on a tile of the map, we will be more or
//    less close to the edges. This distance changes if we go on the right,
//    left, up or down direction from where the player is.
// 2) Let's say pos_x = 4.8. wich means: map_x = 4.
//    If we go on the right direction(ray_dir_x > 0) step will be set at 1 to
//    indicate that we go forward on the x axe. 
// 3) To find the distance between the player and the first time we enconter
//    the x edge it is gonna be the dist_next_x multiplied by the distance of
//    the player with the edge.
//    Here: 4 + 1 - 4.8 = 0.2. so dist_next_x will be multiplied by 0.2.
//
// The distance player-edge will always be under 1, or exactly 1, since we are
// on cellules of 1 x 1.

void	stop_at_first_edge(t_ray *ray, t_map *map, double dist_next_x,
													double dist_next_y)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->wall_dist_x = (map->player_pos_x - map->wall_pos_x)
			* dist_next_x;
	}
	else
	{
		ray->step_x = 1;
		ray->wall_dist_x = (map->wall_pos_x + 1 - map->player_pos_x)
			* dist_next_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->wall_dist_y = (map->player_pos_y - map->wall_pos_y)
			* dist_next_y;
	}
	else
	{
		ray->step_y = 1;
		ray->wall_dist_y = (map->wall_pos_y + 1 - map->player_pos_y)
			* dist_next_y;
	}
}

// 1) We first want to know the distance we have to travel from an edge x or y,
//    to another (this will depend on the ray direction).
// 2) Then let's position ourself on the perfect edge of x and y.
// 3) From where we are now, we add dist_next_x or y to be exactly on the next
//    edge x or y.
//
// dist_next_x or y cannot be negatif and we turn them positif when needed.

void	detect_first_wall(t_cub3d *cub3d)
{
	double	dist_next_x;
	double	dist_next_y;

	dist_next_x = 1 / cub3d->ray->dir_x;
	if (dist_next_x < 0)
		dist_next_x = -dist_next_x;
	dist_next_y = 1 / cub3d->ray->dir_y;
	if (dist_next_y < 0)
		dist_next_y = -dist_next_y;
	cub3d->map->wall_pos_x = (int)cub3d->map->player_pos_x;
	cub3d->map->wall_pos_y = (int)cub3d->map->player_pos_y;
	stop_at_first_edge(cub3d->ray, cub3d->map, dist_next_x, dist_next_y);
	until_we_hit_a_wall(cub3d->map, cub3d->ray, dist_next_x, dist_next_y);
}

// 1) After getting the main_ray_dir and his plane vector, we search the rays
//    direction with the camera orientation associated (begin on the far left).
// 2) For every ray, the camera orient a tiny bit to the right, updating itself 
//    with the current ray_dir we are calculating.
//
// Casting the curr_column and win_width in double ensure having a precised 
// result. without it we had an overflow.

void	curr_ray_dir(t_cub3d *cub3d)
{
	float	camera;

	camera = 2 * ((double)cub3d->curr_column / (double)WIN_WIDTH) - 1;
	cub3d->ray->dir_x = cub3d->ray->main_dir_x
		+ (cub3d->ray->main_plane_x * camera);
	cub3d->ray->dir_y = cub3d->ray->main_dir_y
		+ (cub3d->ray->main_plane_y * camera);
}

// From our first column(0), to the last one(WIN_WIDTH - 1), we are looking for
// precious informations to help us draw the right pixel(ceil, texture or
// floor), at the right screen position.

void	ray_casting(t_cub3d *cub3d)
{
	curr_ray_dir(cub3d);
	detect_first_wall(cub3d);
}
