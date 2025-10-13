#ifndef EXEC_H
# define EXEC_H

# include "cub3D.h"
# include "set_mlx.h"
# include "math.h"

# define M_PI 3.14159
typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;

typedef struct s_ray
{
	float 		radian;
	float 		main_vector; //v_radian anciennement
	float 		main_ray_dir_x;
	float 		main_ray_dir_y;
	float 		main_ray_plane_x;
	float 		main_ray_plane_y;
	float		dir_x;
	float		dir_y;
	float		dist_next_x;
	float		dist_next_y;
	float		wall_dist_x;
	float		wall_dist_y;
	float		perp_wall_dist;
	float		camera;
	int			step_x;
	int			step_y;
	bool		side;
}			t_ray;

typedef struct s_map
{
	char 			**map;
	float 			player_pos_x;
	float 			player_pos_y;
	unsigned int	wall_pos_x;
	unsigned int	wall_pos_y;
	float 			player_orientation;
}			t_map;

//draw_column.c
void	draw_column(t_cub3d *cub3d);

//print_screen.c
void	print_screen(t_cub3d *cub3d);

//exec.c
int		exec(t_cub3d *cub3d);

//draw.c
int	    draw_pixel(t_cub3d *cub3d, char *area, unsigned int pixel);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif