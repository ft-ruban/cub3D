/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:32:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/11/02 10:53:38 by ldevoude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// free everything in set (may be nice to modify that function to create smth)
// that handle all of our struct maybe?

static void	free_parsing_content(t_parsing *parsing)
{
	if (parsing->buff)
		free(parsing->buff);
	if (parsing->rp_no)
		free(parsing->rp_no);
	if (parsing->rp_so)
		free(parsing->rp_so);
	if (parsing->rp_we)
		free(parsing->rp_we);
	if (parsing->rp_ea)
		free(parsing->rp_ea);
}

static void	destroy_images_free_ray(t_cub3d *cub3d, unsigned char return_value)
{
	if (return_value >= 31 || return_value == ALL_OK)
		free(cub3d->ray);
	if (return_value >= 30 || return_value == ALL_OK)
		mlx_destroy_image(cub3d->mlx->ptr, cub3d->texture->ea->img);
	if (return_value >= 29 || return_value == ALL_OK)
		mlx_destroy_image(cub3d->mlx->ptr, cub3d->texture->we->img);
	if (return_value >= 28 || return_value == ALL_OK)
		mlx_destroy_image(cub3d->mlx->ptr, cub3d->texture->so->img);
	if (return_value >= 27 || return_value == ALL_OK)
		mlx_destroy_image(cub3d->mlx->ptr, cub3d->texture->no->img);
}

static void	free_texture_mlx_struct(t_cub3d *cub3d, unsigned char return_value)
{
	if (return_value >= 26 || return_value == ALL_OK)
	{
		free(cub3d->texture->no);
		free(cub3d->texture->so);
		free(cub3d->texture->ea);
		free(cub3d->texture->we);
	}
	if (return_value >= 25 || return_value == ALL_OK)
	{
		destroy_free_screen(cub3d->mlx);
		free(cub3d->mlx->screen);
		free(cub3d->mlx);
	}
	if (return_value >= 24 || return_value == ALL_OK)
		free(cub3d->texture);
}

static void	free_parsing_con_struct(t_cub3d *cub3d, unsigned char return_value)
{
	if (return_value >= 17 || return_value == ALL_OK)
		free_map(cub3d->map);
	else if (return_value >= 15 || return_value == ALL_OK)
	{
		free(cub3d->map->map);
		free(cub3d->map);
	}
	else if (return_value >= 13 || return_value == ALL_OK)
		free(cub3d->map);
	if (return_value >= 7 || return_value == ALL_OK)
		free_parsing_content(cub3d->parsing);
	if (return_value >= 5 || return_value == ALL_OK)
		free(cub3d->parsing);
	if (return_value >= 2 || return_value == ALL_OK)
		free(cub3d);
}

int	clean_and_exit(t_cub3d *cub3d)
{
	unsigned char	return_value;

	return_value = cub3d->error_type;
	destroy_images_free_ray(cub3d, return_value);
	free_texture_mlx_struct(cub3d, return_value);
	free_parsing_con_struct(cub3d, return_value);
	get_next_line(-1);
	return (return_value);
}
