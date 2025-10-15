#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// we are now on the edge of x and y, so to go forward we are gonna add
// one dist_next_x or y. then everytime we move to the next edge, we keep an
// eye on where we are by updating the map_x or y with the right step(+1 or -1).
// the side variable is here to indicate if we hit a wall on the x or y side.

void	until_we_hit_a_wall(t_map *map, t_ray *ray,
			unsigned int dist_next_x,unsigned int dist_next_y)
{
	while (map->map[map->wall_pos_y][map->wall_pos_x] != 1)
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

// depending on where we are on a cellule of the map, we will be more or
// less close to the edges. also this distance is different if we go on the
// right, left, up or dow direction.
// let's say pos_x = 4.8. then map_x = 4. if we go on the right direction, then
// ray_dir_x > 0 and step = 1. 
// So to find the distance between the player and the first time we enconter
// the x edge, we add dist_next_x that we multipy by a number bellow 1.
// here 4 + 1 - 4.8 = 0.2. so dist_next_x will be multiplied by 0.2. 

void	stop_at_first_edge(t_ray *ray, t_map *map, unsigned int dist_next_x,
													unsigned int dist_next_y)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->wall_dist_x = (map->player_pos_x - map->wall_pos_x) *
															dist_next_x;
	}
	else
	{
		ray->step_x = 1;
		ray->wall_dist_x = (map->wall_pos_x + 1 - map->player_pos_x) *
															dist_next_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->wall_dist_y = (map->player_pos_y - map->wall_pos_y) *
															dist_next_y;
	}
	else
	{
		ray->step_y = 1;
		ray->wall_dist_y = (map->wall_pos_y + 1 - map->player_pos_y) *
															dist_next_y;
	}
}

// we first want to know the distance we have to travel, giving the ray
// direction, until we cross the next x or y edge.
// then the distance in between the player and the next edge may not be exactly
// the same as this distance(x to x + 1). So we also find this exact distance.
// Now it's easy, from where we are now, (wich is exactly on the edge of an 
// axe), we add dist_next_x or y to be exactly on the next edge x or y.

void	detect_first_wall(t_cub3d *cub3d)
{
	unsigned int	dist_next_x;
	unsigned int	dist_next_y;

	dist_next_x = 1 / cub3d->ray->dir_x;
	dist_next_y = 1 / cub3d->ray->dir_y;
	stop_at_first_edge(cub3d->ray, cub3d->map, dist_next_x, dist_next_y);
	until_we_hit_a_wall(cub3d->map, cub3d->map->map, dist_next_x, dist_next_y);
}

// after getting the main_ray_dir and his plane vecteur, we calculate the rays
// (for each camera position).
// for every ray, we calculate the distance in between the player and the wall,
// and then we move to the next ray.
// for every time we calculate a ray direction, the camera orient a tiny bit to
// the left, updating itself with the current ray_dir we are calculating.

void	curr_ray_dir(t_cub3d *cub3d)
{
	float	camera;

	camera = 2 * (cub3d->curr_column / WIN_WIDTH) - 1;
	cub3d->ray->dir_x = cub3d->ray->main_ray_dir_x +
					(cub3d->ray->main_ray_plane_x * camera);
	cub3d->ray->dir_y = cub3d->ray->main_ray_dir_y +
					(cub3d->ray->main_ray_plane_y * camera);
}

void	print_screen(t_cub3d *cub3d)
{
	cub3d->curr_column = 0;
	while (cub3d->curr_column < WIN_WIDTH)
	{
		curr_ray_dir(cub3d);
		detect_first_wall(cub3d);
		draw_column(cub3d);
		cub3d->curr_column++;
	}
}
