#ifndef EXEC_H
# define EXEC_H

# include "cub3D.h"
# include "set_mlx.h"
# include "math.h"

//# define M_PI 3.14159
typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;

typedef struct s_ray
{
	float 		wall_pos_x;
	float 		wall_pos_y;
	float 		radian;
	float 		main_vector; //v_radian anciennement
	float 		main_ray_dir_x;
	float 		main_ray_dir_y;
	float 		main_ray_plane_x;
	float 		main_ray_plane_y;
}			t_ray;

typedef struct s_map
{
	char 		**map;
	float 		player_pos_x;
	float 		player_pos_y;
	float 		player_orientation;
}			t_map;

//draw.c
int	    draw(t_mlx *mlx);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif