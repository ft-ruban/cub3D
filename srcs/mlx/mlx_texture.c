/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:48:53 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/01 14:27:37 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "set_mlx.h"

static bool init_ray(t_cub3d *cub3d)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	if(!ray)
	{
		return (RETURN_FAILURE);
	}
	cub3d->ray = ray;
	return(RETURN_SUCCESS);
}

static bool free_all_err(t_img *no, t_img *ea, t_img *so, t_img *we)
{
	if(no)
		free(no);	
	if(ea)
		free(ea);
	if(so)
		free(so);
	if(we)
		free(we);
	return(1);
}

static bool malloc_cardinal_point_struct(t_texture *texture)
{
	t_img 		*no;
	t_img  		*so;
	t_img  		*we;
	t_img  		*ea;

	no = NULL;
	so = NULL;
	we = NULL;
	ea = NULL;
	no = malloc(sizeof(t_img));
	so = malloc(sizeof(t_img));
	we = malloc(sizeof(t_img));
	ea = malloc(sizeof(t_img));
	if (!no || !so || !we || !ea)
		return(free_all_err(no, ea, so, we));
	texture->no = no;
	texture->so = so;
	texture->we = we;
	texture->ea = ea;
	return(RETURN_SUCCESS);
}

static bool init_img_texture(t_img *texture, t_cub3d *cub3d, char *path)
{
	texture->img = mlx_xpm_file_to_image(cub3d->mlx->ptr, path,
		&texture->width, &texture->height);
	if(!texture->img)
	 	return(RETURN_FAILURE);
	texture->addr = mlx_get_data_addr(texture->img, &(texture->bits_per_pixel),
	 &(texture->line_length), &(texture->endian));
	texture->bits_per_pixel = texture->bits_per_pixel >> 3;
	return(RETURN_SUCCESS);
}

static bool init_textures_img(t_cub3d *cub3d)
{
	if(malloc_cardinal_point_struct(cub3d->texture))
		return(error_handler(cub3d, INIT_IMG_TEXT_FAIL, "TOFILL", MSG_33));
	if(init_img_texture(cub3d->texture->no, cub3d, cub3d->parsing->rp_no))
		return(error_handler(cub3d, TEXTURE_NO_FAIL, "TOFILL", MSG_34));
	if(init_img_texture(cub3d->texture->so, cub3d, cub3d->parsing->rp_so))
	{
		return(error_handler(cub3d, TEXTURE_SO_FAIL, "TOFILL", MSG_35));
	}
	if(init_img_texture(cub3d->texture->we, cub3d, cub3d->parsing->rp_we))
	{
		return(error_handler(cub3d, TEXTURE_WE_FAIL, "TOFILL", MSG_36));
	}
	if(init_img_texture(cub3d->texture->ea, cub3d, cub3d->parsing->rp_ea))
	{
		return(error_handler(cub3d, TEXTURE_EA_FAIL, "TOFILL", MSG_37));
	}
	return(RETURN_SUCCESS);
}


int init_mlx_texture_img(t_cub3d *cub3d)
{
	t_mlx *mlx;

	mlx = NULL;
	mlx = init_screen_mlx(cub3d, mlx);
	if (!mlx)
		return(error_handler(cub3d, INIT_MLX_FAIL, "main:TOFILL ", MSG_32));
	if(init_textures_img(cub3d))
	 	return(RETURN_FAILURE);
	if	(init_ray(cub3d))
		return(error_handler(cub3d, INIT_RAY_FAIL, "main:TOFILL ", MSG_32));
	init_player_data(cub3d);
	return(RETURN_SUCCESS);
}