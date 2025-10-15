#ifndef SET_MLX_H
# define SET_MLX_H

# include "../minilibx-linux/mlx.h"
# include "cub3D.h"

# define TRUE 1
# define FALSE 0
# define WIN_WIDTH 500
# define WIN_HEIGHT 500
# define TEXTURE_WIDTH 1000
# define TEXTURE_HEIGHT 1000
# define KEY_ESC 65307
# define KEY_UNKNOWN 0

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_texture
{
	int floor_hex;
	int ceil_hex;
	t_img *t_no;
	t_img *t_so;
	t_img *t_ea;
	t_img *t_we;
}				t_texture;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_img		*screen;
}				t_mlx;

typedef struct s_texture
{
	unsigned int	wall_pixel_height;
	unsigned int	pixel_color;
	unsigned int	*ceil_hex;
	unsigned int	*floor_hex;
	float			render;
	unsigned int	y;
	unsigned int	x;
	t_img			*no;
	t_img			*so;
	t_img			*we;
	t_img			*ea;
}				t_texture;

// commands.c
int	handle_keys(int keycode, t_mlx *screen);
int	close_window(t_mlx *screen);

// mlx_utils.c
void 	hook_and_loop(t_cub3d *cub3d, t_mlx *screen);
void 	destroy_free_screen(t_mlx *screen);
void	*init_screen_mlx(t_mlx *t_mlx);
// int				free_all_mlx(t_mlx *screen, t_set_call *param, int error_code);
#endif