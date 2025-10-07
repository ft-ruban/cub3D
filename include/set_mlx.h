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
	void		*no_img;
	char		*no_addr;
	void		*so_img;
	char		*so_addr;
	void		*we_img;
	char		*we_addr;
	void		*ea_img;
	char		*ea_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
}				t_mlx;

// commands.c
int	handle_keys(int keycode, t_mlx *screen);
int	close_window(t_mlx *screen);

// mlx_utils.c
void 	hook_and_loop(t_mlx *screen);
void 	destroy_free_screen(t_mlx *screen);
void	*init_screen_mlx(t_mlx *t_mlx);
// int				free_all_mlx(t_mlx *screen, t_set_call *param, int error_code);
#endif