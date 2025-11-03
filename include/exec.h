/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:04 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/03 20:51:19 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "cub3D.h"
# include "math.h"
# include "stdbool.h"

# define PI 3.14159

typedef struct s_mlx		t_mlx;
typedef struct s_cub3d		t_cub3d;
typedef struct s_texture	t_texture;

typedef struct s_ray
{
	float					radian;
	float					main_vector;
	float					main_dir_x;
	float					main_dir_y;
	float					main_plane_x;
	float					main_plane_y;
	float					dir_x;
	float					dir_y;
	float					dist_next_x;
	float					dist_next_y;
	float					wall_dist_x;
	float					wall_dist_y;
	float					perp_wall_dist;
	float					camera;
	int						step_x;
	int						step_y;
	bool					side;
}							t_ray;

typedef struct s_map
{
	char					**map;
	float					player_pos_x;
	float					player_pos_y;
	unsigned int			wall_pos_x;
	unsigned int			wall_pos_y;
	float					player_orientation;
}							t_map;

// column_pixels_put.c
void						column_pixels_put(t_cub3d *cub3d,
								t_texture *texture, unsigned int wall_start,
								unsigned int wall_end);

// column_pixels_update.c
void						column_pixels_update(t_cub3d *cub3d);

// exec.c
int							exec(t_cub3d *cub3d);

//init_exec_struct.c
int							init_exec_struct(t_cub3d *cub3d);

// init_mlx_texture_img.c
int							init_mlx_texture_img(t_cub3d *cub3d);

// init_player_data.c
void						init_player_data(t_cub3d *cub3d);

// ray_casting.c
void						ray_casting(t_cub3d *cub3d);

// my_mlx_pixel_put.c
void						my_mlx_pixel_put(t_mlx *mlx, unsigned int color,
								unsigned int x, unsigned int y);

#endif