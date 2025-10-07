#ifndef EXEC_H
# define EXEC_H

# include "cub3D.h"
# include "set_mlx.h"
# include "math.h"

# define M_PI 3.141592653589793238462643383279502984

typedef struct s_data
{
	float 		wall_pos_x;
	float 		wall_pos_y;
	float 		player_pos_x;
	float 		player_pos_y;
	float 		player_orientation;
	float 		radian;
	float 		v_radian;
	float 		*main_ray_dir;
	float 		*main_ray_plane;
	float 		*all_ray_dir;
	t_texture	*texture;
}				t_data;

//draw.c
int	    draw(t_mlx *mlx);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif