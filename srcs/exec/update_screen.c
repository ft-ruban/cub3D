#include "parsing.h"
#include "set_mlx.h"
#include "exec.h"

// 
void	avoid_fish_eye(t_data *data)
{
	if (data->side = 0)
		data->perp_wall_dist = (data->map_x - data->pos_x +
						(1 - data->step_x) / 2) / data->ray_dir_x;
	else
		data->perp_wall_dist = (data->map_y - data->pos_y +
						(1 - data->step_y) / 2) / data->ray_dir_y;
}

// here we are now on the edge of x and y, so to go forward we are gonna add
// one dist_next_x or y. then everytime we move to the next edge, we keep an
// eye on where we are by updating the map_x or y with the right step(+1 or -1).
// the side variable is here to indicate if we hit a wall on the x or y side.
void	until_we_hit_a_wall(t_data *data, t_settings *set,
			unsigned int dist_next_x,unsigned int dist_next_y)
{
	while (set->map[data->map_y][data->map_x] != 1)
	{
		if (data->wall_dist_x < data->wall_dist_y)
		{
			data->wall_dist_x += dist_next_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->wall_dist_y += dist_next_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
	}
	avoid_fish_eye(data);
}

// here, depending on where we are on a cellule of the map, we will be more or
// less close to the edges. also this distance is different if we go on the
// right, left, up or dow direction.
// let's say pos_x = 4.8. then map_x = 4. if we go on the right direction, then
// ray_dir_x > 0 and step = 1. 
// So to find the distance between the player and the first time we enconter
// the x edge, we add dist_next_x that we multipy by a number bellow 1.
// here 4 + 1 - 4.8 = 0.2. so dist_next_x will be multiplied by 0.2. 
void	stop_at_first_edge(t_data *data, unsigned int dist_next_x,
											unsigned int dist_next_y)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->wall_dist_x = (data->pos_x - data->map_x) * dist_next_x;
	}
	else
	{
		data->step_x = 1;
		data->wall_dist_x = (data->map_x + 1 - data->pos_x) * dist_next_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->wall_dist_y = (data->pos_y - data->map_y) * dist_next_y;
	}
	else
	{
		data->step_y = 1;
		data->wall_dist_y = (data->map_y + 1 - data->pos_y) * dist_next_y;
	}
}

// we first want to know the distance we have to travel, giving the ray
// direction, until we cross the next x or y edge.
// then the distance in between the player and the next edge may not be exactly
// the same as this distance(x to x + 1). So we also find this exact distance.
// Now it's easy, from where we are now, (wich is exactly on the edge of an 
// axe), we add dist_next_x or y to be exactly on the next edge x or y.
void	detect_first_wall(t_data *data, t_settings *set)
{
	unsigned int	dist_next_x;
	unsigned int	dist_next_y;

	dist_next_x = 1 / data->ray_dir_x;
	dist_next_y = 1 / data->ray_dir_y;
	stop_at_first_edge(data, dist_next_x, dist_next_y);
	until_we_hit_a_wall(data, set, dist_next_x, dist_next_y);
}

// after getting the main_ray_dir and his plane vecteur, we calculate the rays
// (for each camera position).
// for every ray, we calculate the distance in between the player and the wall,
// and then we move to the next ray.
// for every time we calculate a ray direction, the camera orient a tiny bit to
// the left, updating itself with the current ray_dir we are calculating.
void	update_ray_dir(t_data *data, unsigned int curr_column)
{
	float	camera;

	camera = 2 * (curr_column / WIN_WIDTH) - 1;
	data->ray_dir_x = data->main_ray_dir_x +
					(data->main_ray_plane_x * camera);
	data->ray_dir_y = data->main_ray_dir_y +
					(data->main_ray_plane_y * camera);
}

update_screen(t_data *data, t_settings *set)
{
	unsigned int curr_column;

	curr_column = 0;
	while (curr_column < WIN_WIDTH)
	{
		update_ray_dir(data, curr_column);
		detect_first_wall(data, set);
		curr_column++;
	}
}
