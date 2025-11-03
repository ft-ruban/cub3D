/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:54 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/03 15:06:15 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "exec.h"
# include "parsing.h"
# include "set_mlx.h"
# include "utils.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

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
	INIT_MLX_FAIL,
	INIT_IMG_TEXT_FAIL,
	TEXTURE_NO_FAIL,
	TEXTURE_SO_FAIL,
	TEXTURE_WE_FAIL,
	TEXTURE_EA_FAIL,
	INIT_RAY_FAIL,
}					t_error_status;

typedef struct s_cub3d
{
	unsigned int	curr_column;
	bool			print;
	t_parsing		*parsing;
	t_map			*map;
	t_ray			*ray;
	t_texture		*texture;
	t_mlx			*mlx;
	unsigned char	error_type;
}					t_cub3d;

#endif