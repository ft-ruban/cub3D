/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:41:54 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 13:41:55 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_MLX_H
# define SET_MLX_H

# include "../minilibx-linux/mlx.h"
# include "cub3D.h"

# define TRUE 1
# define FALSE 0
# define WIN_WIDTH 1980
# define WIN_HEIGHT 1080
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define KEY_ESC 65307
# define KEY_FORWARD 65362
# define KEY_BACKWARD 65364
# define KEY_W 119
# define KEY_S 115
# define STEP 0.5
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_A 97
# define KEY_D 100
# define ROTATION 0.5
# define KEY_UNKNOWN 0

typedef struct s_ray	t_ray;
typedef struct s_map	t_map;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct s_mlx
{
	void				*ptr;
	void				*mlx_win;
	t_img				*screen;
}						t_mlx;

typedef struct s_texture
{
	unsigned int		wall_pixel_height;
	unsigned int		pixel_color;
	unsigned int		ceil_hex;
	unsigned int		floor_hex;
	unsigned int		y;
	unsigned int		x;
	int					offset;
	float				render;
	t_img				*no;
	t_img				*so;
	t_img				*we;
	t_img				*ea;
}						t_texture;

// commands.c
int						handle_keys(int keycode, t_cub3d *cub3d);
int						close_window(t_mlx *screen);

// directions.c
void					go_forward(t_cub3d *cub3d, t_ray *ray, t_map *map);
void					go_backward(t_cub3d *cub3d, t_ray *ray, t_map *map);
void					go_left(t_cub3d *cub3d, t_ray *ray, t_map *map);
void					go_right(t_cub3d *cub3d, t_ray *ray, t_map *map);

// mlx_utils.c
void					hook_and_loop(t_cub3d *cub3d, t_mlx *screen);
void					destroy_free_screen(t_mlx *screen);
void					*init_screen_mlx(t_cub3d *cub3d, t_mlx *t_mlx);

// mlx_texture.c
int						init_mlx_texture_img(t_cub3d *cub3d);

#endif