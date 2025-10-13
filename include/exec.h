#ifndef EXEC_H
# define EXEC_H

# include "cub3D.h"
# include "set_mlx.h"
# include "math.h"

# define M_PI 3.14159

typedef struct s_data
{
	unsigned int	side;
	unsigned int	map_x;
	unsigned int	map_y;
	unsigned int	wall_pixel_height;
	unsigned int	curr_column;
	int				step_x;
	int				step_y;
	float 			pos_x;
	float 			pos_y;
	float 			wall_dist_x;
	float 			wall_dist_y;
	float 			perp_wall_dist;
	float 			player_orientation;
	float 			main_ray_dir_x;
	float 			main_ray_dir_y;
	float 			main_ray_plane_x;
	float 			main_ray_plane_y;
	float			ray_dir_x;
	float			ray_dir_y;
	int				pixel_color;
	t_texture	*texture;
}				t_data;

//draw_column.c
void	draw_column(t_data *data, t_mlx *mlx, t_texture *texture);

//print_screen.c
void	print_screen(t_data *data, t_settings *set, t_mlx *mlx, t_texture *texture);

//exec.c
int		exec(t_data *data, t_settings *set, t_mlx *mlx, char **map);

//draw.c
int	    draw(t_mlx *mlx);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif