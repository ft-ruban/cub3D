#ifndef SET_MLX_H
# define SET_MLX_H

# include "../minilibx-linux/mlx.h"
# include "cub3D.h"

# define TRUE 1
# define FALSE 0
# define WIN_WIDTH 500
# define WIN_HEIGHT 500
# define X_MIN -2.0
# define X_MAX 1.0
# define Y_MIN -1.5
# define Y_MAX 1.5

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
}				t_mlx;

typedef struct s_complex
{
	double		real_x;
	double		imaginary_y;
}				t_complex;

typedef struct s_set_call
{
	t_mlx		*screen;
	t_complex	*c;
	t_complex	*z;
	double		zoom;
	int			color_factor;
}				t_set_call;

typedef struct s_utils
{
	double		x;
	double		y;
	int			iter;
	double		xtemp;
}				t_utils;

// commands.c
int	handle_keys(int keycode, t_set_call *param);
int	close_window(t_set_call *param);


// placeholder.c
int				init_param(t_set_call *param, t_mlx *screen);
void			*init_screen_mlx(t_mlx *t_mlx);

#endif