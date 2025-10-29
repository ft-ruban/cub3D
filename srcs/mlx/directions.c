#include "set_mlx.h"

void	go_forward(t_cub3d *cub3d, t_ray *ray, t_map *map)
{
	if (map->map
		[(int)map->player_pos_y]
		[(int)(map->player_pos_x + ((STEP + 0.25) * ray->main_dir_x))] != '1')
	{
		map->player_pos_x += (STEP * ray->main_dir_x);
	}
	if (map->map
		[(int)(map->player_pos_y + ((STEP + 0.25) * ray->main_dir_y))]
		[(int)map->player_pos_x] != '1')
	{
		map->player_pos_y += (STEP * ray->main_dir_y);
	}
	cub3d->print = true;
}

void	go_backward(t_cub3d *cub3d, t_ray *ray, t_map *map)
{
	if (map->map
		[(int)map->player_pos_y]
		[(int)(map->player_pos_x - ((STEP + 0.25) * ray->main_dir_x))] != '1')
	{
		map->player_pos_x -= (STEP * ray->main_dir_x);
	}
	if (map->map
		[(int)(map->player_pos_y - ((STEP + 0.25) * ray->main_dir_y))]
		[(int)map->player_pos_x] != '1')
	{
		map->player_pos_y -= (STEP * ray->main_dir_y);
	}
	cub3d->print = true;
}

void	go_left(t_cub3d *cub3d, t_ray *ray, t_map *map)
{
	if (map->map
		[(int)map->player_pos_y]
		[(int)(map->player_pos_x - ((STEP + 0.25) * ray->main_plane_x))] != '1')
	{
		map->player_pos_x -= (STEP * ray->main_plane_x);
	}
	if (map->map
		[(int)(map->player_pos_y - ((STEP + 0.25) * ray->main_plane_y))]
		[(int)map->player_pos_x] != '1')
	{
		map->player_pos_y -= (STEP * ray->main_plane_y);
	}
	cub3d->print = true;
}

void	go_right(t_cub3d *cub3d, t_ray *ray, t_map *map)
{
	if (map->map
		[(int)map->player_pos_y]
		[(int)(map->player_pos_x + ((STEP + 0.25) * ray->main_plane_x))] != '1')
	{
		map->player_pos_x += (STEP * ray->main_plane_x);
	}
	if (map->map
		[(int)(map->player_pos_y + ((STEP + 0.25) * ray->main_plane_y))]
		[(int)map->player_pos_x] != '1')
	{
		map->player_pos_y += (STEP * ray->main_plane_y);
	}
	cub3d->print = true;
}
