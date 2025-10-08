#ifndef CUB3D_H
# define CUB3D_H

# include "debug.h"
//#include "utils.h"
# include <stdlib.h> //size_t

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1
# define NONE_ASSIGNED -1
# define MSG_ERR_MLX "MLX initiation failed\n"

typedef enum e_error_status
{
	ALL_OK,
	MAL_ERR_SET = 1,
	ERR,
	PAR_NBR_ARGC,
	PAR_EXTENSION,
	INV_FAIL,
	MAL_ERR_BUFF,
	INV_CON,
	INV_READ,
	PAR_INV_RGB,
	GNL_FAILED,
	STRJOIN_FAILED,
	INV_MAP,
    INIT_LIBX_FAILED ,
}					t_error_status;

typedef struct s_cub3D
{
    t_parsing *parsing;
    t_ray     *ray;
    t_player  *player;
    t_texture *texture;
    t_mlx     *mlx;
}               t_cub3D;

//typedef struct s_

typedef struct s_settings
{
    char *buff;
    char *rp_no;
    char *rp_so;
    char *rp_we;
    char *rp_ea;
    int floor_r;
    int floor_g;
    int floor_b;
    int ceil_r;
    int ceil_g;
    int ceil_b;
    unsigned char error_type;
}						t_settings;

//main_utils.c
void	init_struct_value(t_settings *set);
void	free_all(t_settings *set);
int	    clean_and_exit(t_settings *set);



// typedef struct s_img
// {
// 	void		*img;
// 	char		*addr;
// 	int			bits_per_pixel;
// 	int			line_length;
// 	int			endian;
// }				t_img;

// typedef struct s_mlx
// {
// 	void		*mlx;
// 	void		*mlx_win;
// 	t_img		img;
// }				t_mlx;

#endif