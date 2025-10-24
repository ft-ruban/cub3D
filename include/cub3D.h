#ifndef CUB3D_H
# define CUB3D_H

# include "debug.h"
//#include "utils.h"
# include <stdlib.h> //size_t

typedef struct s_parsing	t_parsing;
typedef struct s_map		t_map;
typedef struct s_texture	t_texture;
typedef struct s_mlx 		t_mlx;
typedef struct s_ray		t_ray;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1
# define NONE_ASSIGNED -1
# define MSG_ERR_MLX "MLX initiation failed\n"
# define BEFORE_PARSING_INIT 5

typedef enum e_error_status
{
	ALL_OK,
	CUB_SET_FAIL,
	PAR_NBR_ARGC,
	PAR_EXTENSION,
	PARSING_INIT_FAIL,
	OPEN_FD_ELE,
	MAL_ERR_BUFF,
	INV_CON_ELE,
	ELEMENT_MISS,
	INV_CON_RGB,
	GNL_FAILED,
	STRJOIN_FAILED,
	FAIL_INIT_MAP,
	FAIL_READ_MAP,
	FAIL_MALLOC_MAP,
	FAIL_OPEN_MAP,
	FAIL_CP_MAP,
	READ_MAP_CHECK,
	MAP_NOT_SINGLE,
	MULTIPLE_PLAYERS,
	INVALID_MAP_CHAR,
	NO_PLAYER_FOUND,
	MAP_NOT_ENCLOSED,
    INIT_TEXTURE_FAIL,
	INIT_TEXTURE_FAIL
}					t_error_status;

typedef struct s_cub3d
{
	unsigned int	curr_column; //Ray?
    t_parsing   	*parsing;
	t_map  			*map;
    t_ray     		*ray;
    t_texture 		*texture;
    t_mlx     		*mlx;
	unsigned char error_type;
}               t_cub3d;

//typedef struct s_

// typedef struct s_settings
// {
//     char *buff;
//     char *rp_no;
//     char *rp_so;
//     char *rp_we;
//     char *rp_ea;
//     int floor_r;
//     int floor_g;
//     int floor_b;
//     int ceil_r;
//     int ceil_g;
//     int ceil_b;
//     unsigned char error_type;
// }						t_settings;

//main_utils.c
//void	init_parsing_struct(t_parsing *parsing, t_cub3d *cub3d);
// void	free_all(t_settings *set);
int	    clean_and_exit(t_cub3d *cub3d);



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